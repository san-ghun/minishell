/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:18:03 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/29 23:19:48 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hdoc	*hdoc(void)
{
	static t_hdoc	this;
	static int		is_init;

	if (is_init)
		return (&this);
	this = (t_hdoc){
		.line = NULL,
	};
	is_init = TRUE;
	return (&this);
}
