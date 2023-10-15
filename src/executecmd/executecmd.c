/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:06:17 by minakim           #+#    #+#             */
/*   Updated: 2023/10/15 21:36:25 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int get_numpipe(t_sent *cmd)
//{
//	int	numpipe;
//
//	numpipe = 0;
//	while (cmd)
//	{
//		if (cmd->output_flag == PIPE_FLAG)
//			numpipe++;
//		cmd = cmd->next;
//	}
//	return (numpipe);
//}

int	execute_node(t_sent *node, char *menvp[], char *path)
{
	size_t	tmp_size;
	char	**tmp;

	if (node->tokens[0] == NULL || path == NULL)
		return (-1);
	if (node->tokens[0][0] == '/')
	{
		tmp_size = ms_split_size(node->tokens[0], '/');
		tmp = (char **)malloc(sizeof(char *) * (tmp_size + 1));
		tmp = ms_split_process(node->tokens[0], '/', tmp, 0);
		node->tokens[0] = ft_strdup(tmp[tmp_size - 1]);
		ft_free_2d(tmp);
	}
	execve(path, node->tokens, menvp);
	ms_error("Failed to execute command\n");
	return (-1);
}

//void	close_all_pipe(t_deque *deque)
//{
//	t_sent	*cmd;
//
//	cmd = deque->end;
//	while (cmd)
//	{
//		if (cmd->output_flag == PIPE_FLAG)
//		{
//			printf("parent %d close: fd[%d]\n", getpid(), cmd->fd[0]);
//			close(cmd->fd[0]);
//
//			printf("parent %d close: fd[%d]\n", getpid(), cmd->fd[1]);
//			close(cmd->fd[1]);
//		}
//		cmd = cmd->next;
//	}
//}

int	ft_execvp(t_sent *cmd)
{
	char	**menvp;
	char	*path;
	int		bt;

	bt = -1;
	menvp = dll_to_envp(ms_env());
	path = ms_find_path(cmd->tokens[0]);
	if (cmd->output_flag == STDERR_FILENO)
	{
		ms_error(cmd->output_argv);
		return (ft_free_check(path, menvp, 1));
	}
	if (check_path(path, cmd->tokens[0]))
		return (ft_free_check(path, menvp, 1));
	bt = dispatchcmd_wrapper(cmd);
	if (bt < 0)
		return (-1);
	if (bt == 0)
		if (execute_node(cmd, menvp, path) < 0)
			return (ft_free_check(path, menvp, -1));
	return (ft_free_check(path, menvp, 0));
}

int	wait_child(int pid)
{
	int status;
	int	res;
	t_elst	*lst;

	status = 0;
	res = 0;
	lst = ms_env();
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && lst->g_exit != 130)
		res = WTERMSIG(status);
	else if (WIFEXITED(status) && lst->g_exit != 130)
		res = WEXITSTATUS(status);
	else if (WIFSTOPPED(status) && lst->g_exit != 130)
		res = 1;
	return (res);
}

///	If it's not the first command,
/// the child's standard input is replaced with the read end of the previous pipe.
/// If it's not the last command,
/// the child's standard output is replaced with the write end of the current pipe.
int	executecmd(t_deque *deque)
{
	t_sent	*cmd;
	int		pid;
	int		pipe_open;

	cmd = deque->end;
	while (cmd) {
		cmd = deque_pop_back(deque);
		pipe_open = 0;
		if (cmd->output_flag == PIPE_FLAG || (cmd->prev && cmd->prev->output_flag == PIPE_FLAG)) {
			pipe_open = 1;
			if (pipe(cmd->pipes))
				return (-1);
		}

		pid = fork();

		if (pid < 0) {
			perror("fork()");
			return (-1);
		} else if (pid == 0) /// child process
		{
			/// call redirection
			if (run_by_flag(cmd, INPUT) < 0)
				return (-1);
			if (run_by_flag(cmd, OUTPUT) < 0)
				return (-1);

			ft_execvp(cmd);
			exit(1);
		}
		/// parent process

	}
	return (0);
}


