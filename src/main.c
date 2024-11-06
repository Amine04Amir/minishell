#include "minishell.h"

t_global g_mini;

int empty_prompt(char *rl)
{
	int i;

	i = 0;
	while (rl[i] && (rl[i] != ' ' && rl[i] != '\t'))
	{
		i++;
	}
	return i;
}


void	prompt(char **env)
{
	char	*rl;
	t_list	*list;
	t_env *env_list;
	
	env_list = NULL;
	list = NULL;
	ft_env(env, &env_list);
	while (1)
	{
		g_mini.command = malloc(sizeof(t_cmd));
		g_mini.command->files = NULL;
		g_mini.command->heredoc = NULL;
		g_mini.command->next = NULL;
		rl = readline("minishell$ ");
		if (rl == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (empty_prompt(rl) == 0)
		{
			free(rl);
			continue;
		}
		lexer(rl, &list);
		syntax_error(list);
		parser(list);
		expand(env_list);
		// for (int i = 0; g_mini.command->cmd[i]; i++) 
		// {
    	// 	printf("gcmd[%d] : %s (length: %zu)\n", i, g_mini.command->cmd[i], strlen(g_mini.command->cmd[i]));
		// }
		if (!run_builtins(&env_list))
			run_cmd(g_mini.command, env_list);
		ft_lstclear(&list);
		add_history(rl);
		free(rl);
	}
	//rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac == 1)
		prompt(env);
	else
		return (1);
	return (0);
}