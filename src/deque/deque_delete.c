/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:39:17 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/07 22:22:06 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	deque_del(t_deque *deque);
t_sent	*deque_pop_front(t_deque *deque);
t_sent	*deque_pop_back(t_deque *deque);

void	deque_del(t_deque *deque)
{
	free(deque);
}

t_sent	*deque_pop_front(t_deque *deque)
{
	t_sent	*target;

	if (!deque_size(deque))
		return (NULL);
	target = deque->begin;
	deque->begin = target->prev;
	if (deque->begin == NULL)
		deque->end = NULL;
	else
		deque->begin->next = NULL;
	deque->size--;
	return (target);
}

t_sent	*deque_pop_back(t_deque *deque)
{
	t_sent	*target;

	if (!deque_size(deque))
		return (NULL);
	target = deque->end;
	deque->end = target->next;
	if (deque->end == NULL)
		deque->begin = NULL;
	else
		deque->end->prev = NULL;
	deque->size--;
	return (target);
}
