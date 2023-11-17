/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_onecmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:30:08 by minakim           #+#    #+#             */
/*   Updated: 2023/11/17 14:42:32 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redirections(t_ctx *c);

int	ft_execvp_onecmd(t_sent *cmd, t_deque *deque)
{
	int		pid;
	int		res;
	t_ctx	*c;

	res = 0;
	pid = fork();
	if (check_pid(pid))
		return (-1);
	else if (pid == 0)
	{
		if (run_by_flag(cmd, INPUT) < 0)
			return (-1);
		if (run_by_flag(cmd, OUTPUT) < 0)
			return (-1);
		c = ms_ctx();
		setup_redirections(c);
		res = ft_execvp(cmd);
		if (res == -1 || res == 1)
			ft_ms_exit(cmd, deque, 127);
	}
	ms_ctx()->wait_count = 1;
	return (res);
}

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

int	executed_onecmd(t_sent *cmd, t_deque *deque)
{
	int		res;
	t_ctx	*c;

	res = 0;
	c = ms_ctx();

	if (cmd->tokens[0] == NULL)
		return (-1);
	if (is_built_in(cmd))
	{	/// @note -1 is error, should return ft_error();
		if (run_by_flag(cmd, INPUT) < 0)
			return (-1);
		if (run_by_flag(cmd, OUTPUT) < 0)
			return (-1);
		if (save_or_rollback(SAVE_STREAMS) < 0)
			return (-1);
		setup_redirections(c);
		res = dispatchcmd_wrapper(cmd);
		if (save_or_rollback(ROLLBACK_STREAMS) < 0)
			return (-1);
		if (res < 0)
			return (res);
	}
	else
		res = ft_execvp_onecmd(cmd, deque);
	return (res);
}

int	singlecmd(t_sent *cmd, t_deque *deque)
{
	int	status;
	int	res;
	int	exit;

	exit = executed_onecmd(cmd, deque);
	if (exit < 0)
		return (-1);
	res = 0;
	status = 0;
	if (ms_ctx()->wait_count == 1)
		wait(&status);
	if (WIFSIGNALED(status) && ms_env()->g_exit != 130)
		res = WTERMSIG(status);
	else if (WIFEXITED(status) && ms_env()->g_exit != 130)
		res = WEXITSTATUS(status);
	else if (WIFSTOPPED(status) && ms_env()->g_exit != 130)
		res = 1;
	ms_env()->g_exit = res;
	return (res);
}
