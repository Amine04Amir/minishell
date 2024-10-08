/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:49:46 by mamir             #+#    #+#             */
/*   Updated: 2024/09/29 23:43:57 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd(char **args) 
{
    char *home = getenv("HOME");


    if (args[1] == NULL) 
    {
        if (chdir(home) != 0)
            perror("cd");
    } 
    else if (strcmp(args[1], "-") == 0) 
    {
        char *oldpwd = getenv("OLDPWD");
        if (oldpwd) 
        {
            if (chdir(oldpwd) == 0)
                printf("%s\n", oldpwd);
            else
                perror("cd");
        } 
        else 
        {
            fprintf(stderr, "OLDPWD not set\n");
        }
    }
    else 
    {
        if (chdir(args[1]) != 0)
            perror("cd");
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", cwd, 1);
    } 
    else 
    {
        perror("getcwd");
    }
}

void pwd(void) 
{
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    } 
    else 
    {
        perror("getcwd() error");
    }
}
