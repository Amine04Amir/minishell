/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:43:34 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/01 15:39:46 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*ft_file_new(char *filename, t_token type, char *delimiter)
{
	t_file	*new;

	new = malloc(sizeof(t_cmd));
	new->filename = filename;
	new->delimiter = delimiter;
	new->type = type;
	new->next = NULL;
	return (new);
}
