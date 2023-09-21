/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:01:20 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/18 18:51:10 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		child_proc(t_sent *cmd, t_elst *lst, int *fd, int prev_fd);
void		parent_proc(int pid, t_sent *cmd, int *fd, int *prev_fd);

void	executecmd(t_deque *deque, t_elst *lst)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	t_sent	*cmd;

	init_fd(fd);
	prev_fd = -1;
	while (deque->size > 0)
	{
		cmd = deque_pop_back(deque);
		if (cmd->output_flag == PIPE_FLAG)
			pipe(fd);
		if (dispatchcmd(cmd, lst))
			return ;
		pid = fork();
		if (pid < 0)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			child_proc(cmd, lst, fd, prev_fd);
		else
			parent_proc(pid, cmd, fd, &prev_fd);
	}
}

void	child_proc(t_sent *cmd, t_elst *lst, int *fd, int prev_fd)
{
	char	**menvp;

	run_by_flag(cmd, lst, INPUT);
	if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmd->output_flag == PIPE_FLAG && fd[1] != -1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	run_by_flag(cmd, lst, OUTPUT);
	menvp = dll_to_envp(lst);
	execute_node(cmd, lst, menvp);
	ft_free_2d(menvp);
	exit(EXIT_SUCCESS);
}

void	parent_proc(int pid, t_sent *cmd, int *fd, int *prev_fd)
{
	waitpid(pid, NULL, 0);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->output_flag == PIPE_FLAG)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

void	execute_node(t_sent *node, t_elst *lst, char *menvp[])
{
	char	*path;

	path = ms_find_path(node->tokens[0], menvp);
	if (node->tokens[0] == NULL || path == NULL)
		exit(EXIT_SUCCESS);
	(void) lst;
	execve(path, node->tokens, menvp);
	perror("Error"); // TODO: ERROR
	ft_putstr_fd("Failed to execute command\n", 2);
	exit(EXIT_FAILURE);
}
