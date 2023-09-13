/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 00:00:52 by minakim           #+#    #+#             */
/*   Updated: 2023/09/13 15:46:12 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: implement heredoc handling and execution
void	execute_heredoc(t_sent *node, t_elst *lst)
{
	/// execute
	execute_node(node, lst);
}

// implement input redirection read handling and execution
void	execute_redi_read(t_sent *node, t_elst *lst)
{
	int		fd;
	int		saved_stdin;
	char	*filename;

	filename = setfilename(node->tokens, "<");
	printf("file : %s\n", filename);
	if (!filename)
		return ; /// ERROR
	fd = open(filename, O_RDONLY);
	if (exe_error(fd, "Failed to open file for input redirection"))
		return;
	// save stdin
	saved_stdin = dup(STDIN_FILENO);
	if (exe_error(saved_stdin, "Failed to duplicate stdin") ||
		exe_error(dup2(fd, STDIN_FILENO), "Failed to duplicate file descriptor to stdin"))
	{
		close(fd);
		return;
	}
	remove_redi_tokens(node, "<");
	/// execute
	execute_node(node, lst);
	// recover stdin
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(fd);
}

// TODO: implement input pipe handling and execution
void	execute_pipe_input(t_sent *node, t_elst *lst)
{
	execute_node(node, lst);
}
