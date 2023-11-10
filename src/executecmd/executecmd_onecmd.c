/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_disptach_handler_util.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:38:49 by minakim           #+#    #+#             */
/*   Updated: 2023/11/10 16:31:19 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int executed_a_cmd(t_sent *cmd)
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
		res = ft_execvp(cmd);
	return (res);
}

int	onecmd(t_sent *cmd)
{
	int	status;
	int	res;

	if (executed_a_cmd(cmd) < 0)
		return (-1);
	res = 0;
	status = 0;
	if (WIFSIGNALED(status) && ms_env()->g_exit != 130)
		res = WTERMSIG(status);
	else if (WIFEXITED(status) && ms_env()->g_exit != 130)
		res = WEXITSTATUS(status);
	else if (WIFSTOPPED(status) && ms_env()->g_exit != 130)
		res = 1;
	ms_env()->g_exit = res;
	return (res);
}
