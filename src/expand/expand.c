/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:02:51 by mamir             #+#    #+#             */
/*   Updated: 2024/12/04 18:08:10 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void merge_export_assignment(t_list **list)
{
    t_list *current;

    current = *list;
    while (current && current->next)
    {
        if (strcmp(current->content, "export") == 0 && current->next)
        {
            t_list *var_node = current->next;
            t_list *val_node = var_node->next;
    
            // Check if var_node contains '=' and val_node exists
            if (val_node && ft_strchr(var_node->content, '=') != NULL)
            {
                char *merged_content;
                size_t len_var = strlen(var_node->content);
                size_t len_val = strlen(val_node->content);

                // Allocate space for merged string
                merged_content = malloc(len_var + len_val + 1); // +1 for null terminator
                if (!merged_content)
                    return;

                // Merge variable name and value
                strcpy(merged_content, var_node->content);
                strcat(merged_content, val_node->content);

                // Determine if quotes should be removed
                size_t len = strlen(merged_content);
                if (len >= 2 &&
                    ((merged_content[len - len_val] == '\'' &&
                      merged_content[len - 1] == '\'') ||
                     (merged_content[len - len_val] == '"' &&
                      merged_content[len - 1] == '"')))
                {
                    // Remove quotes if it's a single word in quotes
                    if (!strchr(val_node->content, ' '))
                    {
                        merged_content[len - 1] = '\0';
                        ft_memmove(merged_content + len_var,
                                merged_content + len_var + 1,
                                ft_strlen(merged_content + len_var + 1) + 1);
                    }
                }

                // Update var_node with merged content
                free(var_node->content);
                var_node->content = merged_content;

                // Remove val_node
                var_node->next = val_node->next;
                if (val_node->next)
                    val_node->next->prev = var_node;
                free(val_node->content);
                free(val_node);

                continue; // Recheck current node after merge
            }
        }
        current = current->next;
    }
}


int	ensure_buffer_space(t_parse_state *state, size_t needed)
{
	size_t	new_size;
	char	*new_buf;

	if (state->result_idx + needed < state->result_size)
		return (1);
	new_size = state->result_size * 2;
	if (new_size < state->result_idx + needed)
		new_size = state->result_idx + needed + 1;
	new_buf = realloc(state->result, new_size);
	if (!new_buf)
		return (0);
	state->result = new_buf;
	state->result_size = new_size;
	return (1);
}

void	handle_dollar_cases(t_parse_state *state)
{
	// Special case: lone $
	if (!state->line[state->i] || 
		!(ft_isalnum(state->line[state->i]) || state->line[state->i] == '_'))
	{
		if (!ensure_buffer_space(state, 1))
			return ;
		
		if (!state->in_single_quote)
		{
			state->result[state->result_idx++] = '$';
		}
		return ;
	}
}

void	handle_quotes(t_parse_state *state)
{
	if (!ensure_buffer_space(state, 1))
		return ;
	if (state->line[state->i] == '\'' && !state->in_double_quote)
	{
		state->in_single_quote = !state->in_single_quote;
		state->result[state->result_idx++] = state->line[state->i++];
	}
	else if (state->line[state->i] == '\"' && !state->in_single_quote)
	{
		state->in_double_quote = !state->in_double_quote;
		state->result[state->result_idx++] = state->line[state->i++];
	}
	else
	{
		state->result[state->result_idx++] = state->line[state->i++];
	}
}

void	init_parse_state(t_parse_state *state, char *line, t_env *env)
{
	state->result_size = (ft_strlen(line) * 2) + 1;
	state->result = malloc(state->result_size);
	if (!state->result)
	{
		state->result_size = 0;
		return ;
	}
	state->in_single_quote = 0;
	state->in_double_quote = 0;
	state->result_idx = 0;
	state->line = line;
	state->i = 0;
	state->env = env;
}

void process_quotes(t_quote_state *state)
{
    if ((state->str[state->i] == '\'' && !state->in_double) ||
        (state->str[state->i] == '\"' && !state->in_single))
    {
        if (state->str[state->i] == '\'')
            state->in_single = !state->in_single;
        else
            state->in_double = !state->in_double;
        state->i++;
    }
    else
    {
        state->result[state->j++] = state->str[state->i++];
    }
}

char *remove_quotes(char *str)
{
    char *result;
    int i, j, len, in_single, in_double;

    if (!str)
        return (NULL);

    len = ft_strlen(str);
    result = malloc(len + 1);
    if (!result)
        return (NULL);

    i = 0;
    j = 0;
    in_single = 0;
    in_double = 0;

    while (str[i])
    {
        if (str[i] == '\'' && !in_double)
            in_single = !in_single;
        else if (str[i] == '\"' && !in_single)
            in_double = !in_double;
        else
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}


char *expand_variable(t_env *env, const char *var_name)
{
    t_env *current = env;

    // Traverse the environment linked list to find the variable
    while (current)
    {
        if (strcmp(current->key, var_name) == 0)
            return current->value;  // Return the value of the variable
        current = current->next;
    }

    // If the variable doesn't exist, return NULL (or empty string "")
    return NULL;  // or return "" if you prefer empty string
}



void copy_var_value(t_parse_state *state, char *value)
{
    size_t value_len;

    if (!value)
        return;

    value_len = ft_strlen(value);
    if (!ensure_buffer_space(state, value_len))
        return;

    ft_memcpy(&state->result[state->result_idx], value, value_len);
    state->result_idx += value_len;
}

void handle_regular_var(t_parse_state *state)
{
    char var_name[256];
    size_t var_idx = 0;
    char *value = NULL;

    // Special case: handle lone `$`
    if (!state->line[state->i] || !(ft_isalnum(state->line[state->i]) || state->line[state->i] == '_'))
    {
        if (!ensure_buffer_space(state, 1))
            return;
        state->result[state->result_idx++] = '$';
        return;
    }

    // Collect variable name
    while (state->line[state->i] &&
           (ft_isalnum(state->line[state->i]) || state->line[state->i] == '_') &&
           var_idx < sizeof(var_name) - 1)
    {
        var_name[var_idx++] = state->line[state->i++];
    }
    var_name[var_idx] = '\0';

    // Expand variable
    if (strcmp(var_name, "?") == 0)
        value = "0"; // Replace with last exit status
    else
        value = expand_variable(state->env, var_name);

    // Append variable value to result buffer
    if (value)
    {
        size_t value_len = ft_strlen(value);
        if (ensure_buffer_space(state, value_len))
        {
            ft_memcpy(&state->result[state->result_idx], value, value_len);
            state->result_idx += value_len;
        }
    }
}

void	process_char(t_parse_state *state)
{
	if (state->i >= ft_strlen(state->line))
		return ;

	if (state->line[state->i] == '\'' || state->line[state->i] == '\"')
		handle_quotes(state);
	else if (state->line[state->i] == '$')
	{
		state->i++;
		handle_regular_var(state);
	}
	else
	{
		if (!ensure_buffer_space(state, 1))
			return ;
		state->result[state->result_idx++] = state->line[state->i++];
	}
}

char *expand_variables(t_env *env, char *line)
{
    t_parse_state state;
    char *expanded_line;

    if (!line)
        return (NULL);

    init_parse_state(&state, line, env);
    if (!state.result)
        return (NULL);

    while (line[state.i])
    {
        process_char(&state);
    }

    if (!ensure_buffer_space(&state, 1))
    {
        free(state.result);
        return (NULL);
    }

    state.result[state.result_idx] = '\0';

    expanded_line = remove_quotes(state.result);
    free(state.result);

    return expanded_line;
}


int	should_merge_with_next(char *current, char *next)
{
	size_t	cur_len;

	if (!next)
		return (0);

	cur_len = ft_strlen(current);
	return ((!ft_strchr("'\"", current[0]) && cur_len > 0 &&
			(current[cur_len - 1] == '\'' || current[cur_len - 1] == '\"')) ||
			(current[0] != '\'' && current[0] != '\"' &&
			 (next[0] == '\'' || next[0] == '\"')));
}

char *merge_args(char *arg1, char *arg2)
{
    char *merged;
    size_t len1 = ft_strlen(arg1);
    size_t len2 = ft_strlen(arg2);

    merged = malloc(len1 + len2 + 1);  // Allocate space for the combined string
    if (!merged)
        return NULL;

    ft_strlcpy(merged, arg1, len1 + 1);  // Copy first argument
    ft_strlcat(merged, arg2, len1 + len2 + 1);  // Concatenate the second argument

    return merged;
}

void expand(t_env *env, t_list **list)
{
    t_list *current;
    char *expanded_line;

    current = *list;

    while (current)
    {
        // Check if the node content is not empty
        if (current->content && current->content[0] != '\0') // Skip empty nodes
        {
            // Call expand_variables to expand the content of the current node
            expanded_line = expand_variables(env, current->content);

            // If the expanded value is NULL (non-existent variable), handle it
            if (expanded_line == NULL)
            {
                // If the variable doesn't exist, replace content with empty string
                free(current->content);
                current->content = strdup("");  // Or "" if you prefer an empty string
            }
            else
            {
                // Otherwise, update the node content with the expanded value
                free(current->content);
                current->content = expanded_line;
            }
        }

        // Move to the next node
        current = current->next;
    }
}

