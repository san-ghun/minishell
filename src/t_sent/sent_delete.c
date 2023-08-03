/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:48 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/03 11:59:08 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sent_del(t_sent *sent);
void	sent_delone(t_sent *sent[], t_sent *target);
void	sent_delall(t_sent *sent[]);

void	sent_del(t_sent *sent)
{
	sent->prev = NULL;
	sent->next = NULL;
	// free(sent->tokens);
	free(sent->p_unit);
	free(sent);
}

void	sent_delone(t_sent *sent[], t_sent *target)
{
	if (!sent || !target)
		return ;
	if ((target->prev == NULL) && (target->next == NULL))
	{
		*sent = NULL;
		sent_del(target);
		return ;
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
	sent_del(target);
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
