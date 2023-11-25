/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_singlecmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:30:08 by minakim           #+#    #+#             */
/*   Updated: 2023/11/24 17:33:13 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_execvp_builtin(t_sent *cmd)
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
		if (save_or_rollback(SAVE_STREAMS) < 0)
			return (-1);
		if (run_by_flag(cmd, INPUT) < 0)
			return (-1);
		if (run_by_flag(cmd, OUTPUT) < 0)
			return (-1);
		c = ms_ctx();
		setup_redirections(c);
		res = dispatchcmd_wrapper(cmd);
		if (save_or_rollback(ROLLBACK_STREAMS) < 0)
			return (-1);
	}
	ms_ctx()->wait_count = 1;
	return (res);
}

int	ft_execvp_builtin_no_fork(t_sent *cmd, t_ctx *c)
{
	int		res;

	res = 0;
	if (save_or_rollback(SAVE_STREAMS) < 0)
		return (-1);
	if (run_by_flag(cmd, INPUT) < 0)
		return (-1);
	if (run_by_flag(cmd, OUTPUT) < 0)
		return (-1);
	setup_redirections(c);
	res = dispatchcmd_wrapper(cmd);
	if (save_or_rollback(ROLLBACK_STREAMS) < 0)
		return (-1);
	return (res);
}

/// @note -1 is error, should return ft_error();
int	executed_onecmd(t_sent *cmd, t_deque *deque)
{
	int		res;
	t_ctx	*c;

	res = 0;
	c = ms_ctx();
	if (is_built_in(cmd))
	{
		/// @note fork : 만약에 필요하면 다시 살려서 하기 (export, env .. )
//		if (cmd->input_flag == REDI_RD_FLAG || cmd->input_flag == HDOC_FLAG)
//			res = ft_execvp_builtin(cmd);
//		else
//		{
			res = ft_execvp_builtin_no_fork(cmd, c);
			if (res < 0)
				return (res);
//		}
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
	// if (WIFSIGNALED(status) && ms_env()->g_exit != 130)
	if (WIFSIGNALED(status))
	{
		res = WTERMSIG(status) + 128;
		if (res == 141)
			res = 0;
	}
	else if (WIFEXITED(status) && ms_env()->g_exit != 130)
		res = WEXITSTATUS(status);
	else if (WIFSTOPPED(status) && ms_env()->g_exit != 130)
		res = 1;
	// else if (ms_env()->g_exit <= 256)
	// 	return (ms_env()->g_exit);
	ms_env()->g_exit = res;
	return (res);
}
