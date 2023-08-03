/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:12 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/03 11:50:15 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sent	*sent_new(char *p_unit, char **tokens, int is_redir, int is_pipe);
void	sent_addfront(t_sent *sent[], t_sent *new);
void	sent_addback(t_sent *sent[], t_sent *new);

t_sent	*sent_new(char *p_unit, char **tokens, int is_redir, int is_pipe)
{
	t_sent	*this;

	this = (t_sent *)malloc(sizeof(t_sent));
	if (!this)
		return (NULL);
	this->p_unit = ft_strdup(p_unit);
	this->tokens = tokens;
	this->is_redir = is_redir;
	this->is_pipe = is_pipe;
	this->is_quote = 0;
	this->prev = NULL;
	this->next = NULL;
	return (this);
}

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
