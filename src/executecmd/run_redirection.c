/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runredi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:12:54 by minakim           #+#    #+#             */
/*   Updated: 2023/11/16 17:26:40 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// implement input redirection read handling and execution
int	flag_redi_read(t_sent *node, t_elst *lst)
{
	char	*filename;
	int		fd;
	t_ctx	*c;

	(void)lst;
	c = ms_ctx();
	filename = node->input_argv;
	fd = open_file(filename, 2);
	if (fd == -1)
		return (fd);
	c->input_fd = fd;
	return (0);
}

// Implement output redirection write append handling and execution
int	flag_redi_append(t_sent *node, t_elst *lst)
{
	char	*filename;
	int		fd;
	t_ctx	*c;

	(void) lst;
	filename = node->output_argv;
	c = ms_ctx();
	fd = open_file(filename, 0);
	if (fd == -1)
		return (fd);
	c->output_fd = fd;

	return (0);
}

// Implement output redirection write trunc handling and execution
int	flag_redi_trunc(t_sent *node, t_elst *lst)
{
	char	*filename;
	int		fd;
	t_ctx	*c;

	(void) lst;
	filename = node->output_argv;
	c = ms_ctx();
	fd = open_file(filename, 1);
	if (fd == -1)
		return (fd);
	c->output_fd = fd;
	return (0);
}
