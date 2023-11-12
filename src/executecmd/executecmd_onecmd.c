/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_onecmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:30:08 by minakim           #+#    #+#             */
/*   Updated: 2023/11/12 14:30:54 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define SAVE_FD 0
# define RECOVER_FD 1
int save_and_recover(int mode)
{
	t_ctx *c;

	c = ms_ctx();
	if (mode == SAVE_FD)
	{
		c->backup[0] = dup(STDIN_FILENO);
		c->backup[1] = dup(STDOUT_FILENO);
		return (0);
	}
	else if (mode == RECOVER_FD)
	{
		dup2(c->backup[0], STDIN_FILENO);
		dup2(c->backup[1], STDOUT_FILENO);
		return (1);
	}
	else
		return (-1);

}

int	ft_execvp_onecmd(t_sent *cmd, t_deque *deque)
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
		if (res == -1 || res == 1)
			ft_ms_exit(cmd, deque, 127);
	}
	ms_ctx()->wait_count = 1;
	return (res);
}

int	executed_onecmd(t_sent *cmd, t_deque *deque)
{
	int	res;

	res = 0;
	if (save_and_recover(SAVE_FD) < 0)
		return (-1);
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
		res = ft_execvp_onecmd(cmd, deque);
	return (res);
}

int	onecmd(t_sent *cmd, t_deque *deque)
{
	int	status;
	int	res;
	int test;
	t_ctx	*c;

	test = executed_onecmd(cmd, deque);
	if (test < 0)
		return (-1);
	res = 0;
	status = 0;
	if (save_and_recover(RECOVER_FD) < 0)
		return (-1);
	c = ms_ctx();
	if (c->wait_count == 1)
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
