/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:06:17 by minakim           #+#    #+#             */
/*   Updated: 2023/11/01 14:42:17 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		executecmd(t_deque *deque);
int		ft_execvp(t_sent *cmd);
int		execute_node(t_sent *node, char *menvp[], char *path);
int		wait_child(t_ctx *c, int old_fd[2], int wait_count);
void	add_wait_count(int pid);

int	executecmd(t_deque *deque)
{
	t_sent	*cmd;
	int		bt;
	t_ctx	*c;

	c = ms_ctx();
	c->cmd_count = deque->size - 1;
	while (deque->size > 0 && c->i < MAX_PIPES)
	{
		bt = 0;
		cmd = deque_pop_back(deque);
		if (cmd->next && cmd->output_flag == PIPE_FLAG)
			pipe(c->fd);
		if (is_built_in(cmd) == PARENT)
		{
			bt = dispatchcmd_wrapper(cmd, PARENT);
			if (bt < 0)
				return (bt);
			continue ;
		}
		else
			if (run_process(cmd, deque) < 0)
				return (-1);
	}
	return (wait_child(c, c->old_fd, c->wait_count));
}

int	ft_execvp(t_sent *cmd)
{
	char	**menvp;
	char	*path;

	if (cmd->output_flag == STDERR_FILENO)
	{
		ms_error(cmd->output_argv);
		return (1);
	}
	else
	{
		menvp = dll_to_envp(ms_env());
		path = ms_find_path(cmd->tokens[0]);
		if (check_path(path, cmd->tokens[0]))
			return (ft_free_check(path, menvp, 1));
		if (execute_node(cmd, menvp, path) < 0)
			return (ft_free_check(path, menvp, -1));
	}
	return (ft_free_check(path, menvp, 0));
}

int	execute_node(t_sent *node, char *menvp[], char *path)
{
	execve(path, node->tokens, menvp);
	ms_error("Failed to execute command\n");
	return (-1);
}

int	wait_child(t_ctx *c, int old_fd[2], int wait_count)
{
	int	status;
	int	res;
	int	i;

	status = 0;
	res = 0;
	i = -1;
	while (++i < wait_count)
		waitpid(c->pids[i], &status, 0);
	if (c->cmd_count)
	{
		close(old_fd[0]);
		close(old_fd[1]);
	}
	if (WIFSIGNALED(status) && ms_env()->g_exit != 130)
		res = WTERMSIG(status);
	else if (WIFEXITED(status) && ms_env()->g_exit != 130)
		res = WEXITSTATUS(status);
	else if (WIFSTOPPED(status) && ms_env()->g_exit != 130)
		res = 1;
	return (res);
}

void	add_wait_count(int pid)
{
	t_ctx	*context;

	context = ms_ctx();
	context->wait_count += 1;
	context->pids[context->i] = pid;
	context->i += 1;
}
