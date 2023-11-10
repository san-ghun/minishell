/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_onecmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:30:08 by minakim           #+#    #+#             */
/*   Updated: 2023/11/10 19:00:56 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execvp_onecmd(t_sent *cmd)
{
	int	pid;
	int	res;

	res = 0;
	pid = fork();
	if (check_pid(pid))
		return (-1);
	else if (pid == 0)
	{
		res = ft_execvp(cmd);
		return (res);
	}
	ms_ctx()->wait_count = 1;
	return (res);
}

int	executed_onecmd(t_sent *cmd)
{
	int	res;

	res = 0;
	if (run_by_flag(cmd, INPUT) < 0)
		return (-1);
	if (run_by_flag(cmd, OUTPUT) < 0)
		return (-1);
	if (cmd->tokens[0] == NULL)
		return (-1);
	if (is_built_in(cmd))
	{
		res = dispatchcmd_wrapper(cmd);
		if (res < 0)
			return (res);
	}
	else
		ft_execvp_onecmd(cmd);
	return (res);
}

int	onecmd(t_sent *cmd)
{
	int	status;
	int	res;

	if (executed_onecmd(cmd) < 0)
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
