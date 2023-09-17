/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:12:54 by minakim           #+#    #+#             */
/*   Updated: 2023/09/17 13:13:04 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: implement heredoc handling and execution
void execute_heredoc(t_sent *node, t_elst *lst)
{
	(void) node;
	(void) lst;
}

// implement input redirection read handling and execution
void execute_redi_read(t_sent *node, t_elst *lst)
{
	int fd;
	char *filename;

	(void)lst;
	filename = node->input_argv;
	printf("file : %s\n", filename);
	fd = open_file(filename, 2);
	if (exe_error(fd, "Failed to open file for input redirection"))
		return;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

// TODO: implement input pipe handling and execution
void execute_pipe_input(t_sent *node, t_elst *lst)
{
	(void) node;
	(void) lst;
}
