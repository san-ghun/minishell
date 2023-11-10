/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:15:15 by minakim           #+#    #+#             */
/*   Updated: 2023/11/10 01:53:25 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			run_process(t_sent *cmd, t_deque *deque);
int			child(t_sent *cmd, t_deque *deque);
static int	extract_last_path_component(t_sent *cmd);


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
		int status;
		wait(&status);
		res = child(cmd, deque);
		if (res == -1 || res == 1)
			ft_ms_exit(cmd, deque, 127);
	}
	add_wait_count(pid);
	close_fds(cmd, deque, c);
	return (0);
}

static int	extract_last_path_component(t_sent *cmd)
{
	size_t	tmp_size;
	char	**tmp;

	if (cmd->tokens[0] == NULL)
		return (0);
	if (cmd->tokens[0][0] == '/')
	{
		tmp_size = ms_split_size(cmd->tokens[0], '/');
		tmp = (char **)malloc(sizeof(char *) * (tmp_size + 1));
		tmp = ms_split_process(cmd->tokens[0], '/', tmp, 0);
		free(cmd->tokens[0]);
		cmd->tokens[0] = ft_strdup(tmp[tmp_size - 1]);
		ft_free_2d(tmp);
	}
	return (0);
}

int	child(t_sent *cmd, t_deque *deque)
{
	int	res;

	res = 0;
	if (run_by_flag(cmd, INPUT) < 0)
		return (-1);
	if (run_by_flag(cmd, OUTPUT) < 0)
		return (-1);
	if (cmd->output_flag == PIPE_FLAG && cmd->tokens[0] == NULL)
		return (-1);
	update_fd(deque, ms_ctx());
	if (is_built_in(cmd) == CHILD)
	{
		res = dispatchcmd_wrapper(cmd, CHILD);
		exit(0);
	}
	else
		res = ft_execvp(cmd);
	return (res);
}

void	close_fds(t_sent *cmd, t_deque *deque, t_ctx *c)
{
	if (c->cmd_count > deque->size)
	{
		printf("this 2 msgs happens in parent [%s][%d]\n if not first cmd\n", cmd->tokens[0], getpid());
		close(c->old_fd[0]);
		printf("Closed FD %d\n", c->old_fd[0]);
		close(c->old_fd[1]);
		printf("Closed FD %d\n", c->old_fd[1]);
	}
	if (cmd->next)
	{
		printf("this 2 msgs happens in parent [%s][%d]\nif not last cmd\n", cmd->tokens[0], getpid());
		c->old_fd[1] = c->fd[1];
		printf("change FD %d = %d\n", c->old_fd[1], c->fd[1]);
		c->old_fd[0] =  c->fd[0];
		printf("change FD %d = %d\n", c->old_fd[0], c->fd[0]);
	}
	if (!deque->size && !c->cmd_count && c->first_cmd != 1) /// cmd가 하나이고, 시작 cmd가 builtin parent이 아니라면,
	{
		printf("this 2 msgs happens in main process [%d]\n", getpid());
		close(c->old_fd[0]);
		printf("Closed FD %d (last cmd)\n", c->old_fd[0]);
		close(c->old_fd[1]);
		printf("Closed FD %d (last cmd)\n", c->old_fd[1]);
	}
}

void	update_fd(t_deque *deque, t_ctx *c)
{
	if (c->cmd_count > deque->size)
	{
		printf("this 3 msgs happens in child [%d]\n", getpid());
		dup2(c->old_fd[0], STDIN_FILENO);
		printf("dup2 FD %d as %d\n", c->old_fd[0], STDIN_FILENO);
		close(c->old_fd[0]);
		printf("Closed FD %d\n", c->old_fd[0]);
		close(c->old_fd[1]);
		printf("Closed FD %d\n", c->old_fd[1]);

	}
	if (deque->size > 0)
	{
		printf("this 3 msgs happens in child [%d]\n", getpid());
		close(c->fd[0]);
		printf("Closed FD %d\n", c->fd[0]);
		dup2(c->fd[1], STDOUT_FILENO);
		printf("dup2 FD %d as %d\n", c->fd[1], STDIN_FILENO);
		close(c->fd[1]);
		printf("Closed FD %d\n", c->fd[1]);
	}
}