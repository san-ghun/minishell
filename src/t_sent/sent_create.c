/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:12 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/30 16:47:24 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sent	*sent_new(char *p_unit, int is_redir, int is_pipe);

t_sent	*sent_new(char *p_unit, int is_redir, int is_pipe)
{
	t_sent	*this;

	this = (t_sent *)malloc(sizeof(t_sent));
	if (!this)
		return (NULL);
	this->p_unit = p_unit;
	this->tokens_len = 0;
	this->tokens = NULL;
	this->is_redir = is_redir;
	this->is_pipe = is_pipe;
	this->prev = NULL;
	this->next = NULL;
	return (this);
}
