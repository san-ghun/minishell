/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:06:17 by minakim           #+#    #+#             */
/*   Updated: 2023/10/20 16:20:01 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		child(t_sent *cmd, t_deque *deque, int old_fd[2], int fd[2]);
int		ft_execvp(t_sent *cmd);
void	parent(t_sent *cmd, t_deque *deque, int old_fd[2], int fd[2]);
int		wait_child(t_ctx *c, int old_fd[2], int wait_count);
/// TODO : memory leak 체크가 하나도 되어 있지 않으므로 전체적인 구조 수정 이후 디버깅 필요

t_ctx	*ms_ctx(void)
{
	static t_ctx	this;
	static int			is_init;

	if (is_init)
		return (&this);
	is_init = TRUE;
	this.i = 0;
	this.wait_count = 0;
	this.cmd_count = 0;
	return (&this);
}

int extract_last_path_component(t_sent *cmd)
{
	size_t	tmp_size;
	char	**tmp;

	if (cmd->tokens[0] == NULL)
		return (-1);
	if (cmd->tokens[0][0] == '/')
	{
		tmp_size = ms_split_size(cmd->tokens[0], '/');
		tmp = (char **)malloc(sizeof(char *) * (tmp_size + 1));
		tmp = ms_split_process(cmd->tokens[0], '/', tmp, 0);
		cmd->tokens[0] = ft_strdup(tmp[tmp_size - 1]);
		ft_free_2d(tmp);
	}
	return (0);
}

void	add_wait_count(int pid)
{
	t_ctx	*context;

	context = ms_ctx();
	context->wait_count += 1;
	context->pids[context->i] = pid;
	context->i += 1;
}

int	executecmd(t_deque *deque)
{
	t_sent	*cmd;
	int		pid;
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
		{
			if (extract_last_path_component(cmd) < 0)
				return (-1);
			pid = fork();
			if (check_pid(pid))
				return (-1);
			else if (pid == 0) /// child process
				bt = child(cmd, deque, c->old_fd, c->fd);
			if (bt != -1 && bt != 1)
				add_wait_count(pid);
			parent(cmd, deque, c->old_fd, c->fd);
		}
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

int	wait_child(t_ctx *c, int old_fd[2], int wait_count)
{
	int	status;
	int	res;
	int	i;

	status = 0;
	res = 0;
	i = -1;
	if (c->cmd_count)
	{
		close(old_fd[0]);
		close(old_fd[1]);
	}
	while (++i < wait_count)
		waitpid(c->pids[i], &status, 0);
	if (WIFSIGNALED(status) && ms_env()->g_exit != 130)
		res = WTERMSIG(status);
	else if (WIFEXITED(status) && ms_env()->g_exit != 130)
		res = WEXITSTATUS(status);
	else if (WIFSTOPPED(status) && ms_env()->g_exit != 130)
		res = 1;
	return (res);
}

void	fd_handler_child(t_deque *deque, int old_fd[2], int fd[2])
{
	if (ms_ctx()->cmd_count > deque->size)
	{
		dup2(old_fd[0], STDIN_FILENO);
		close(old_fd[0]);
		close(old_fd[1]);
	}
	if (deque->size > 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}
int	child(t_sent *cmd, t_deque *deque, int old_fd[2], int fd[2])
{
	int	res;

	res = 0;
	if (run_by_flag(cmd, INPUT) < 0)
		return (-1);
	if (run_by_flag(cmd, OUTPUT) < 0)
		return (-1);
	fd_handler_child(deque, old_fd, fd);
	if (is_built_in(cmd) == CHILD)
	{
		res = dispatchcmd_wrapper(cmd, CHILD);
		exit(0);
	}
	else
		res = ft_execvp(cmd);
	return (res);
}

void	parent(t_sent *cmd, t_deque *deque, int old_fd[2], int fd[2])
{
	if (ms_ctx()->cmd_count > deque->size)
	{
		close(old_fd[0]);
		close(old_fd[1]);
	}
	if (cmd->next)
	{
		old_fd[1] = fd[1];
		old_fd[0] = fd[0];
	}
}

int	execute_node(t_sent *node, char *menvp[], char *path)
{
	execve(path, node->tokens, menvp);
	ms_error("Failed to execute command\n");
	return (-1);
}