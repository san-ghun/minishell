/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:15:15 by minakim           #+#    #+#             */
/*   Updated: 2023/11/01 19:55:05 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			run_process(t_sent *cmd, t_deque *deque);
int			child(t_sent *cmd, t_deque *deque, int old_fd[2], int fd[2]);
void		parent(t_sent *cmd, t_deque *deque, int old_fd[2], int fd[2]);
static int	extract_last_path_component(t_sent *cmd);
void		fd_handler_child(t_deque *deque, int old_fd[2], int fd[2]);

int	run_process(t_sent *cmd, t_deque *deque)
{
	t_ctx	*c;
	int		res;
	int		pid;

	c = ms_ctx();
	if (extract_last_path_component(cmd) < 0)
		return (-1);
	pid = fork();
	if (check_pid(pid))
		return (-1);
	else if (pid == 0)
	{
		res = child(cmd, deque, c->old_fd, c->fd);
		if (res == -1 || res == 1)
			ft_ms_exit(cmd, deque, 127);
	}
	add_wait_count(pid);
	parent(cmd, deque, c->old_fd, c->fd);
	return (0);
}

static int	extract_last_path_component(t_sent *cmd)
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
