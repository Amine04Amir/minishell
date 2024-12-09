#include "minishell.h"

t_global	g_mini;



int	empty_prompt(char *rl)
{
	int	i;

	i = 0;
	while (rl[i] && (rl[i] != ' ' && rl[i] != '\t'))
	{
		i++;
	}
	return (i);
}
void debug_list(t_list *list)
{
    while (list)
    {
       printf("Node content: %s\n", list->content);
        list = list->next;
    }
}

void	prompt(char **env)
{
	char	*rl;
	t_list	*list;
	t_env	*env_list;

	env_list = NULL;
	list = NULL;
	ft_env(env, &env_list);
	while (1)
	{
		g_mini.sig_flag = 0;
		g_mini.command = _malloc(sizeof(t_cmd), 'm');
		g_mini.command->cmd = NULL;
		g_mini.command->files = NULL;
		g_mini.command->next = NULL;
		signal_handler(IN_PROMPT);
		rl = readline("minishell$ ");
		if (rl == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		g_mini.sig_flag = 1;
		if (empty_prompt(rl) == 0)
		{
			continue ;
		}
		lexer(rl, &list);
		if(!syntax_error(list))
		{
			printf("Before:\n****\n");
			debug_list(list);
			expand(env_list, &list);
			printf("After:\n****\n");
			debug_list(list);
			parser(list);
			run_heredoc(g_mini.command);
			run_cmd(g_mini.command, env_list, env_list);
		}
		signal_handler(IN_PARENT);
		ft_lstclear(&list);
		add_history(rl);
	}
	_malloc(0, 'f');
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac == 1)
		prompt(env);
	else
		return (1);
}
