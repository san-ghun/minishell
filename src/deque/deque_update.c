/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:39:17 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/28 21:37:50 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	deque_update(t_deque *deque, t_sent *old, t_sent *new);

void	deque_update(t_deque *deque, t_sent *old, t_sent *new)
{
	if (!old || !new)
		return ;
	new->prev = old->prev;
	new->next = old->next;
	if (deque->size == 1)
	{
		deque->begin = new;
		deque->end = new;
	}
	else if (deque->begin == old)
	{
		old->next->prev = new;
		deque->begin = new;
	}
	else if (deque->end == old)
	{
		old->prev->next = new;
		deque->end = new;
	}
	else
	{
		old->prev->next = new;
		old->next->prev = new;
	}
	sent_del(old);
}
