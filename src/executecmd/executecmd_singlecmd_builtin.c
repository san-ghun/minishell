/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_singlecmd_builtin.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:39 by minakim           #+#    #+#             */
/*   Updated: 2023/11/23 15:08:17 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redirections(t_ctx *c)
{
	if (c->input_fd != STDIN_FILENO)
	{
		dup2(c->input_fd, STDIN_FILENO);
		close(c->input_fd);
	}
	if (c->output_fd != STDOUT_FILENO)
	{
		dup2(c->output_fd, STDOUT_FILENO);
		close(c->output_fd);
	}
	return (1);
}

int	save_or_rollback(int mode)
{
	static int	original_stdin;
	static int	original_stdout;
	static int	is_saved = FALSE;

	if (is_saved == FALSE && mode == SAVE_STREAMS)
	{
		original_stdin = dup(STDIN_FILENO);
		original_stdout = dup(STDOUT_FILENO);
		is_saved = TRUE;
		return (1);
	}
	else if (is_saved && mode == ROLLBACK_STREAMS)
	{
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
		is_saved = FALSE;
		return (1);
	}
	return (-1);
}
