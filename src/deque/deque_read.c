/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:39:17 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/02 11:49:20 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sent	*deque_at(t_deque *deque, int index);

t_sent	*deque_at(t_deque *deque, int index)
{
	int		i;
	t_sent	*sent;

	if (index >= deque->size)
		return (NULL);
	i = 0;
	sent = deque->begin;
	while (i++ < index)
		sent = sent->prev;
	return (sent);
}
