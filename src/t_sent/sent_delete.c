/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:48 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/28 16:48:29 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sent_delone(t_sent *sent[], t_sent *target);
void	sent_delall(t_sent *sent[]);

void	sent_delone(t_sent *sent[], t_sent *target)
{
	if (!sent || !target)
		return ;
	if ((target->prev == NULL) && (target->next == NULL))
	{
		*sent = NULL;
		return (free(target));
	}
	else if (target->next == NULL)
		target->prev->next = NULL;
	else if (target->prev == NULL)
	{
		target->next->prev = NULL;
		*sent = target->next;
	}
	else
	{
		target->prev->next = target->next;
		target->next->prev = target->prev;
	}
	free(target);
	return ;
}

void	sent_delall(t_sent *sent[])
{
	t_sent	*tmp;
	t_sent	*after;

	if (!sent)
		return ;
	tmp = *sent;
	*sent = NULL;
	while (tmp != NULL)
	{
		after = tmp->next;
		sent_delone(sent, tmp);
		tmp = after;
	}
	return ;
}
