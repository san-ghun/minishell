/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:12 by sanghupa          #+#    #+#             */
/*   Updated: 2023/10/02 22:41:36 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sent	*sent_new(char *p_unit, int input_flag, int output_flag);

t_sent	*sent_new(char *p_unit, int input_flag, int output_flag)
{
	t_sent	*this;

	this = (t_sent *)malloc(sizeof(t_sent));
	if (!this)
		return (NULL);
	this->p_unit = p_unit;
	this->tokens_len = 0;
	this->tokens = NULL;
	this->input_flag = input_flag;
	this->output_flag = output_flag;
	this->input_argv = NULL;
	this->output_argv = NULL;
	this->prev = NULL;
	this->next = NULL;
	return (this);
}
