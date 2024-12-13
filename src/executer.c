#include "minishell.h"

#define WRITE 1
#define READ 0

char	*ft_getenv(char *name, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, name, ft_strlen(env->key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env *env)
{
	char	*path;
	char	**paths;
	int		j;
	char	*fullcmd;

	path = ft_getenv("PATH", env);
	if (path == NULL)
		return (cmd);
	if (cmd == NULL)
		return (NULL);
	//printf("cmd : %s\n", cmd);
	cmd = ft_strjoin("/", cmd);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (NULL);
	j = 0;
	while (paths[j] != NULL)
	{
		fullcmd = ft_strjoin(paths[j], cmd);
		if (access(fullcmd, F_OK) == 0)
			return (fullcmd);
		j++;
	}
	free (cmd);
	return (NULL);
}

char	**convert_env(t_env *list_env)
{
	char	**env;
	int		env_size;
	int		j;
	char	*full_var;

	j = 0;
	env_size = ft_envsize(list_env);
	env = _malloc(sizeof(char *) * (env_size + 1), 'm');
	if (env == NULL)
		return (NULL);
	while (list_env != NULL && j < env_size)
	{
		full_var = ft_strjoin(list_env->key, "=");
		full_var = ft_strjoin(full_var, list_env->value);
		env[j] = full_var;
		j++;
		list_env = list_env->next;
	}
	env[j] = NULL;
	return (env);
}

bool	set_redirections(t_file *file)
{
	int	fd;

	while (file)
	{
		if (file->type == INRED || file->type == HEREDOC)
			fd = open(file->filename, O_RDONLY | O_CREAT, 0644);
		else if (file->type == OUTRED)
			fd = open(file->filename, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		else if (file->type == APPEND)
			fd = open(file->filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			return (perror("minishell$"), false);
		if (file->type == INRED || file->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		file = file->next;
	}
	return (true);
}

int is_builtins(t_cmd *command)
{
    if (strcmp("echo", command->cmd[0]) == 0)
        return (1);
    else if (strcmp("export", command->cmd[0]) == 0)
        return (1);
    else if (strcmp("exit", command->cmd[0]) == 0)
        return (1);
    else if (strcmp("cd", command->cmd[0]) == 0)
        return (1);
    else if (strcmp("pwd", command->cmd[0]) == 0)
       return (1);
    else if (strcmp("env", command->cmd[0]) == 0)
        return (1);
    else if (strcmp("unset",command->cmd[0]) == 0)
        return (1);
    return (0);
}

int	execute_without_path(t_cmd *command)
{
	execve(command->cmd[0], command->cmd, convert_env(g_mini.env));
	perror("minishell$");
	exit(1);
}

int	execute_with_path(t_cmd *command)
{
	char	**env;
	char	*fullcmd;
	
	env = NULL;
	fullcmd = NULL;
	fullcmd = find_path(command->cmd[0], g_mini.env);
	if (fullcmd == NULL)
	{
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": command not found\n", 20);
		exit (127);
	}
	env = convert_env(g_mini.env);
	execve(fullcmd, command->cmd, env);
	perror("minishell$");
	exit(1);
}

int	run_command(t_cmd *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		set_redirections(command->files);
		if (ft_strchr(command->cmd[0], '/') || !get_env(g_mini.env, "PATH")
			|| !*get_env(g_mini.env, "PATH"))
			execute_without_path(command);
		else
			execute_with_path(command);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	execute_command(t_cmd *command)
{
	g_mini.sig_flag = 1;
	if (is_builtins(command))
		run_builtins(&g_mini.env, command);
	else
		run_command(command);
	return (0);
}

int	first_child(pid_t *pid, t_cmd *command, int *fd)
{
	*pid = fork();
	if (*pid == 0)
	{
		// sigexit
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_command(command);
		exit(1);
	}
	return (0);
}

int	second_child(pid_t *pid, t_cmd *command, int *fd)
{
	*pid = fork();
	if (*pid == 0)
	{
		// sigexit
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execution(command);
		exit(1);
	}
	return (0);
}

int	execute_pipe(t_cmd *command)
{
	int		fd[2];
	pid_t	pids[2];


	pipe(fd);
	first_child(&pids[0], command, fd);
	second_child(&pids[1], command->next, fd);
	close(fd[0]);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
	return (0);
}

int	execution(t_cmd *command)
{
	if (command->next)
		execute_pipe(command);
	else
		execute_command(command);
	return (0);
}
