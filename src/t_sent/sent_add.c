/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:56:05 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/24 11:57:16 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sent_addfront(t_sent *sent[], t_sent *new);
void	sent_addback(t_sent *sent[], t_sent *new);

void	sent_addfront(t_sent *sent[], t_sent *new)
{
	t_sent	*head;

	head = *sent;
	if (!sent || !new)
		return ;
	if (!head)
	{
		*sent = new;
		new->prev = NULL;
		new->next = NULL;
		return ;
	}
	head->prev = new;
	new->next = head;
	*sent = new;
	new->prev = NULL;
}

void	sent_addback(t_sent *sent[], t_sent *new)
{
	t_sent	*tail;

	if (!sent || !new)
		return ;
	tail = sent_getlast(*sent);
	if (!tail)
	{
		*sent = new;
		new->prev = NULL;
		new->next = NULL;
		return ;
	}
	tail->next = new;
	new->prev = tail;
	new->next = NULL;
}
