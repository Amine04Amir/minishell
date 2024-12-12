/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:29:48 by mamir             #+#    #+#             */
/*   Updated: 2024/12/12 23:31:38 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}


char	*expand_variable(t_env *env, const char *var_name)
{
	t_env	*current;
	current = env;

	while (current)
	{
		if (ft_strcmp(current->key, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return ("");
}

char	*remove_quotes_and_expand(t_env *env, char *content)
{
	int		i;
	int		j;
	int		in_sq;
	int		in_dq;
	int		name_len;
	char	*expanded;
	char	*var_name;
	char	*var_value;

	i = 0;
	j = 0;
	in_sq = 0;
	in_dq = 0;
	expanded = _malloc(ft_strlen(content) * 2 + 1, 'm');
	if (!expanded)
		return (NULL);
	while (content[i])
	{
		if (content[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (content[i] == '"' && !in_sq)
			in_dq = !in_dq;
		else if (content[i] == '$' && !in_sq)
		{
			i++;
			if (content[i] == '?')
			{
				var_value = ft_itoa(g_mini.exit_status);
				if (!var_value)
					return (NULL);
				ft_strcpy(&expanded[j], var_value);
				j += ft_strlen(var_value);
				free(var_value);
				i++;
			}
			else if (content[i] == '\0' || content[i] == '"' || content[i] == '\'')
				expanded[j++] = '$';
			else
			{
				name_len = 0;
				while (content[i + name_len]
					&& (ft_isalnum(content[i + name_len]) || content[i + name_len] == '_'))
					name_len++;
				if (name_len > 0)
				{
					var_name = _malloc(name_len + 1, 'm');
					if (!var_name)
					{
						free(expanded);
						return (NULL);
					}
					ft_strncpy(var_name, &content[i], name_len);
					var_name[name_len] = '\0';
					var_value = expand_variable(env, var_name);
					ft_strcpy(&expanded[j], var_value);
					j += ft_strlen(var_value);
					free(var_name);
					i += name_len;
				}
			}
		}
		else
			expanded[j++] = content[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

// char *remove_quotes_and_expand(t_env *env, char *content)
// {
    
//     int i = 0, expanded_len = 0;
//     int in_single_quote = 0, in_double_quote = 0;

//     while (content[i])
//     {
//         if (content[i] == '\'' && !in_double_quote)
//         {
//             in_single_quote = !in_single_quote;
//             if (in_single_quote) 
//                 i++;
//             continue;
//         }

//         if (content[i] == '"' && !in_single_quote)
//         {
//             in_double_quote = !in_double_quote;
//             if (in_double_quote) 
//                 i++;
//             continue;
//         }

//         if (content[i] == '$' && !in_single_quote)
//         {
//             i++;
//             if (content[i] == '\0')
//             {
//                 expanded_len++;
//                 continue;
//             }

//             // $? special case
//             if (content[i] == '?')
//             {
//                 char *exit_status = ft_itoa(g_mini.exit_status);
//                 if (exit_status)
//                 {
//                     expanded_len += strlen(exit_status);
//                     free(exit_status);
//                 }
//                 i++;
//                 continue;
//             }

//             // Calculate var name length
//             int name_len = 0;
//             while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
//             {
//                 name_len++;
//                 i++;
//             }

//             // Lookup variable value
//             if (name_len > 0)
//             {
//                 char *var_name = _malloc(name_len + 1, 'm');
//                 if (!var_name)
//                     return NULL;

//                 // Copy var name
//                 ft_strncpy(var_name, &content[i - name_len], name_len);
//                 var_name[name_len] = '\0';

//                 char *var_value = expand_variable(env, var_name);
//                 if (var_value)
//                 {
//                     expanded_len += strlen(var_value);
//                 }
                
//                 free(var_name);
//             }
//         }
//         else
//         {
//             expanded_len++;
//             i++;
//         }
//     }
//     char *expanded_content = _malloc(expanded_len + 1, 'm');
//     i = 0;
//     int j = 0;
//     in_single_quote = 0;
//     in_double_quote = 0;

//     while (content[i])
//     {
//         if (content[i] == '\'' && !in_double_quote)
//         {
//             in_single_quote = !in_single_quote;
//             if (in_single_quote) 
//                 i++;
//             continue;
//         }
//         if (content[i] == '"' && !in_single_quote)
//         {
//             in_double_quote = !in_double_quote;
//             if (in_double_quote) 
//                 i++;
//             continue;
//         }

//         if (content[i] == '$' && !in_single_quote)
//         {
//             i++;
//             if (content[i] == '\0')
//             {
//                 expanded_len++;
//                 continue;
//             }

//             // $? special case
//             if (content[i] == '?')
//             {
//                 char *exit_status = ft_itoa(g_mini.exit_status);
//                 if (exit_status)
//                 {
//                     expanded_len += strlen(exit_status);
//                     free(exit_status);
//                 }
//                 i++;
//                 continue;
//             }

//             // Calculate var name length
//             int name_len = 0;
//             while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
//             {
//                 name_len++;
//                 i++;
//             }

//             // Lookup variable value
//             if (name_len > 0)
//             {
//                 char *var_name = _malloc(name_len + 1, 'm');
//                 if (!var_name)
//                     return NULL;

//                 // Copy var name
//                 ft_strncpy(var_name, &content[i - name_len], name_len);
//                 var_name[name_len] = '\0';

//                 char *var_value = expand_variable(env, var_name);
//                 if (var_value)
//                 {
//                     expanded_len += strlen(var_value);
//                 }
                
//                 free(var_name);
//             }
//         }
//         else
//         {
//             expanded_len++;
//             i++;
//         }
//     }
//     // printf("content: %s\n", expanded_content);

//     expanded_content[j] = '\0';
//     return expanded_content;
// }

void	split_and_expand_variables(t_env *env, t_list **node)
{
	t_list	*current_node;
	char	*expanded_content;

    
	current_node = *node;
	expanded_content = remove_quotes_and_expand(env, current_node->content);
    current_node->content = expanded_content;
}

void expand_variables_in_list(t_env *env, t_list **list)
{
    t_list *current;
    char *expanded_content;

    current = *list;
    while (current)
    {
        if (current->content)
        {
            expanded_content = remove_quotes_and_expand(env, current->content);
            current->content = ft_strdup(expanded_content);
        }
        current = current->next;
    }
}

void merge_fragmented_nodes(t_list **list)
{
    t_list *current = *list;
    t_list *next_node;

    while (current && current->next)
    {
        next_node = current->next;
        if (next_node->separated_by_space == 0)
        {
            char *merged_content = malloc(strlen(current->content) + strlen(next_node->content) + 1);
            if (!merged_content)
                return;

            ft_strcpy(merged_content, current->content);
            ft_strcat(merged_content, next_node->content);
            current->content = merged_content;
            current->next = next_node->next;
            if (next_node->next)
                next_node->next->prev = current;
            free(next_node->content);
            free(next_node);
            continue;
        }
        current = current->next;
    }
}

void	merge_export_assignment(t_list **list)
{
	t_list	*current;
	t_list	*var_node;
	t_list	*val_node;
	char	*val_content;
	size_t	val_len;
	char    *merged_content;
	size_t	len_var;
	size_t	len_val;

	current = *list;
	while (current && current->next)
	{
		if (ft_strcmp(current->content, "export") == 0 && current->next)
		{
			var_node = current->next;
			val_node = var_node->next;
			if (val_node && ft_strchr(var_node->content, '=') != NULL)
			{
				val_content = val_node->content;
				val_len = ft_strlen(val_content);
				if (val_len >= 2 && ((val_content[0] == '\''
							&& val_content[val_len - 1] == '\'')
						|| (val_content[0] == '"'
                                    && val_content[val_len- 1] == '"')))
				{
					len_var = ft_strlen(var_node->content);
					len_val = ft_strlen(val_node->content);
					merged_content = _malloc(len_var + len_val + 1, 'm');
					if (!merged_content)
						return ;
					ft_strcpy(merged_content, var_node->content);
					ft_strcat(merged_content, val_node->content);
					var_node->content = merged_content;
					var_node->next = val_node->next;
					if (val_node->next)
						val_node->next->prev = var_node;
					current = var_node;
					continue ;
				}
			}
		}
		current = current->next;
	}
}

void expand(t_env *env, t_list **list)
{
    merge_export_assignment(list);
    expand_variables_in_list(env, list);
    merge_fragmented_nodes(list);
    t_list *current = *list;
    while (current->next)
    {
        split_and_expand_variables(env, &current);
        current = current->next;
    }
    return ;
}
