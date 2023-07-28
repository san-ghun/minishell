/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:39:17 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/28 21:38:41 by sanghupa         ###   ########.fr       */
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
	deque->begin = target->next;
	if (deque->begin == NULL)
		deque->end = NULL;
	else
		deque->begin->prev = NULL;
	target->prev = NULL;
	target->next = NULL;
	deque->size--;
	return (target);
}

t_sent	*deque_pop_back(t_deque *deque)
{
	t_sent	*target;

	if (!deque_size(deque))
		return (NULL);
	target = deque->end;
	deque->end = target->prev;
	if (deque->end == NULL)
		deque->begin = NULL;
	else
		deque->end->next = NULL;
	target->prev = NULL;
	target->next = NULL;
	deque->size--;
	return (target);
}
