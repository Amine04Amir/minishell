/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:46:08 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/02 13:00:36 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_new(char **content)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->cmd = content;
	new->files = NULL;
	new->next = NULL;
	return (new);
}
