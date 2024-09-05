/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdisplay.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:18:39 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/05 09:26:16 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdisplay(t_list *stack)
{
	printf("lst size : %d\n", ft_lstsize(stack));
	while (stack != NULL)
	{
		printf("node->content : %s\n",stack->content);
		printf("node->type : %u\n",stack->type);
		stack = stack->next;
	}
}
// put this line above inside the while in case of use.
