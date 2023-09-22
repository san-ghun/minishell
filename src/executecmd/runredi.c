/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runredi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:12:54 by minakim           #+#    #+#             */
/*   Updated: 2023/09/22 14:09:35 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// implement input redirection read handling and execution
int	flag_redi_read(t_sent *node, t_elst *lst)
{
	char	*filename;
	int		fd;

	(void)lst;
	filename = node->input_argv;
	fd = open_file(filename, 2);
	if (fd == -1)
		return (fd);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

// Implement output redirection write append handling and execution
int	flag_redi_append(t_sent *node, t_elst *lst)
{
	char	*filename;
	int		fd;

	(void) lst;
	filename = node->output_argv;
	fd = open_file(filename, 0);
	if (fd == -1)
		return (fd);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

// Implement output redirection write trunc handling and execution
int	flag_redi_trunc(t_sent *node, t_elst *lst)
{
	char	*filename;
	int		fd;

	(void) lst;
	filename = node->output_argv;
	fd = open_file(filename, 1);
	if (fd == -1)
		return (fd);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
