#include "minishell.h"

void print_export(t_env *env)
{
	while(env)
	{
		if (env->value == NULL)
            printf("declare -x %s\n", env->key);
		else if (ft_strlen(env->value) == 0)
			printf("declare -x %s\n", env->key);
		else
			printf("declare -x %s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void print_env(t_env *env)
{
	while(env)
	{
		if (env->is_exported == false)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void ft_env(char **env, t_env **env_lst)
{
	t_env *node;

	int i = 0;
	while (env[i])
	{
		char *equal_sign;

		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			node = ft_env_new(env[i], equal_sign + 1);
			*equal_sign = '=';
			if (node)
				ft_env_addback(env_lst, node);
		}
		i++;
	}
}
