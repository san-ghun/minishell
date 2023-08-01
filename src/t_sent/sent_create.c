/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:12 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/01 13:27:29 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sent	*sent_new(char *cmd, int prefix, int suffix);
void	sent_addfront(t_sent *sent[], t_sent *new);
void	sent_addback(t_sent *sent[], t_sent *new);

/*
typedef struct s_sent
{
	char				*cmd;
	int					prefix;
	int					suffix;
	struct s_sent		*prev;
	struct s_sent		*next;
}				t_sent;
*/

t_sent	*sent_new(char *cmd, int prefix, int suffix)
{
	t_sent	*this;

	this = (t_sent *)malloc(sizeof(t_sent));
	if (!this)
		return (NULL);
//	this->cmd = cmd;
//	this->prefix = prefix;
//	this->suffix = suffix;
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
