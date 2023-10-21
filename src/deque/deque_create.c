/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:39:17 by sanghupa          #+#    #+#             */
/*   Updated: 2023/10/20 16:01:43 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_deque	*deque_init(void);
void	deque_push_front(t_deque *deque, t_sent *new);
void	deque_push_back(t_deque *deque, t_sent *new);

t_deque	*deque_init(void)
{
	t_deque	*this;

	this = (t_deque *)malloc(sizeof(t_deque));
	if (!this)
		return (NULL);
	this->begin = NULL;
	this->end = NULL;
	this->size = 0;
	return (this);
}

void	deque_push_front(t_deque *deque, t_sent *new)
{
	if (!new)
		return ;
	if (deque_size(deque) == 0)
	{
		deque->begin = new;
		deque->end = new;
		deque->size++;
		return ;
	}
	sent_addback(&(deque->begin), new);
	deque->begin = new;
	deque->size++;
	return ;
}

void	deque_push_back(t_deque *deque, t_sent *new)
{
	if (!new)
		return ;
	if (deque_size(deque) == 0)
	{
		deque->begin = new;
		deque->end = new;
		deque->size++;
		return ;
	}
	sent_addfront(&(deque->end), new);
	deque->end = new;
	deque->size++;
	return ;
}
