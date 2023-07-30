/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:39:17 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/30 14:39:49 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	deque_size(t_deque *deque);
int		deque_isempty(t_deque *deque);
t_sent	*deque_front(t_deque *deque);
t_sent	*deque_back(t_deque *deque);
void	print_all(t_deque *lst);

size_t	deque_size(t_deque *deque)
{
	return (deque->size);
}

int	deque_isempty(t_deque *deque)
{
	if (deque_size(deque) == 0)
		return (1);
	return (0);
}

t_sent	*deque_front(t_deque *deque)
{
	return (deque->begin);
}

t_sent	*deque_back(t_deque *deque)
{
	return (deque->end);
}

void	print_all(t_deque *lst)
{
	t_sent *node;

	node = lst->begin;
	while(node != NULL)
	{
		ft_printf("%s\n", node->cmd);
		node = node->next;
	}
}