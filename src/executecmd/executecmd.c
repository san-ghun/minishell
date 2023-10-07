/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:01:20 by sanghupa          #+#    #+#             */
/*   Updated: 2023/10/06 17:54:23 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_process(t_sent *cmd, t_elst *lst, int *fd, int *prev_fd);
int		child_proc(t_sent *cmd, int *fd, int *prev_fd);
int		parent_proc(int pid, t_sent *cmd, int *fd, int *prev_fd);

int	executecmd(t_deque *deque)
{
	int		fd[2];
	int		prev_fd;
	int		bt;
	t_sent	*cmd;

	init_fd(fd, &prev_fd);
	while (deque->size > 0)
	{
		cmd = deque_pop_back(deque);
		if (cmd->output_flag == PIPE_FLAG)
			pipe(fd);
		bt = dispatchcmd_wrapper(cmd, fd, &prev_fd);
		if (bt < 0)
			return (-1);
		if (bt)
			continue ;
		if (run_process(cmd, ms_env(), fd, &prev_fd) < 0)
			return (-1);
	}
	return (0);
}

int	run_process(t_sent *cmd, t_elst *lst, int *fd, int *prev_fd)
{
	pid_t	pid;
	char	**menvp;
	char	*path;

	menvp = dll_to_envp(lst);
	path = ms_find_path(cmd->tokens[0], menvp);
	if (cmd->output_flag == STDERR_FILENO)
	{
		ms_error(cmd->output_argv);
		return (ft_free_check(path, menvp, 1));
	}
	if (check_path(path, cmd->tokens[0]))
		return (ft_free_check(path, menvp, 1));
	pid = fork();
	if (check_pid(pid))
		return (ft_free_check(path, menvp, 1));
	if (pid == 0)
	{
		if (child_proc(cmd, fd, prev_fd) < 0)
			return (ft_free_check(path, menvp, -1));
		if (execute_node(cmd, menvp, path) < 0)
			return (ft_free_check(path, menvp, -1));
	}
	lst->g_exit = parent_proc(pid, cmd, fd, prev_fd);
	return (ft_free_check(path, menvp, 0));
}

int	child_proc(t_sent *cmd, int *fd, int *prev_fd)
{
	if (run_by_flag(cmd, INPUT) < 0)
		return (-1);
	if (*prev_fd != -1)
		dup2(*prev_fd, STDIN_FILENO);
	if (cmd->output_flag == PIPE_FLAG && fd[1] != -1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	if (run_by_flag(cmd, OUTPUT) < 0)
		return (-1);
	return (0);
}

int parent_proc(int pid, t_sent *cmd, int *fd, int *prev_fd)
{
	int status;
	int result;

	result = -1;
	if (cmd->input_flag == HDOC_FLAG)
		waitpid(pid, &status, 0);
	else
		waitpid(pid, &status, WNOHANG);
	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->output_flag == PIPE_FLAG)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	return (result);
}

int	execute_node(t_sent *node, char *menvp[], char *path)
{
	if (node->tokens[0] == NULL || path == NULL)
		return (-1);
	execve(path, node->tokens, menvp);
	ms_error("Failed to execute command\n");
	return (-1);
}
