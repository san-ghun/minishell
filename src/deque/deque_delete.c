/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:39:17 by sanghupa          #+#    #+#             */
/*   Updated: 2023/11/25 11:47:54 by sanghupa         ###   ########.fr       */
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
	deque->size--;
	return (target);
}

t_sent	*deque_pop_back(t_deque *deque)
{
	t_sent	*target;

	if (!deque || !deque_size(deque))
		return (NULL);
	if (!deque_size(deque))
		return (NULL);
	target = deque->end;
	if (!target)
		return (NULL);
	deque->end = target->next;
	if (deque->end == NULL)
		deque->begin = NULL;
	deque->size--;
	return (target);
}
