/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:06:17 by minakim           #+#    #+#             */
/*   Updated: 2023/10/16 23:25:17 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		fd[2];
	int		old_fd[2];
	int		first_cmd;

	int i = 0;

	first_cmd = deque->size - 1;

	int pids[first_cmd + 1];
	int multiple_cmds = deque->size > 1;
	while (deque->size > 0)
	{
		cmd = deque_pop_back(deque);
		/// pipe : if there is a next cmd
		if (cmd->next && cmd->output_flag == PIPE_FLAG)
		{
			printf("pipe [%s] cmd\n", cmd->tokens[0]);
			pipe(fd);
		}

		/// fork
		pid = fork();
		if (pid < 0)
		{
			perror("fork()");
			return (-1);
		}
		else if (pid == 0) /// child process
		{
			/// call redirection
			if (run_by_flag(cmd, INPUT) < 0)
				return (-1);
			if (run_by_flag(cmd, OUTPUT) < 0)
				return (-1);

			/// if not first cmd
			if (first_cmd > deque->size)
			{
//				printf("child %d [%s] not first cmd\n", getpid(), cmd->tokens[0]);

				dup2(old_fd[0], STDIN_FILENO);
//				printf("child %d [%s] not first cmd : : close old fds\n", getpid(), cmd->tokens[0]);
				close(old_fd[0]);
//				printf("child %d [%s] not first cmd : close old fds\n",  getpid(), cmd->tokens[0]);
				close(old_fd[1]);
			}
			/// if not last cmd
			if (deque->size > 0)
			{
				printf("child %d [%s] not last cmd\n", getpid(), cmd->tokens[0]);

				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
//				printf("child %d [%s] not last cmd : dup2\n", getpid(), cmd->tokens[0]);
				close(fd[1]);
//				printf("child %d [%s] not last cmd : close fds\n", getpid(), cmd->tokens[0]);
			}
			int res = ft_execvp(cmd);
			return (res);
		}
		else
		{
			/// parent process
			pids[i] = pid;
			/// if there is a previous cmd
			if (first_cmd > deque->size)
			{
//				printf("parent %d [%s] not first cmd\n", getpid(), cmd->tokens[0]);
				close(old_fd[0]);
				close(old_fd[1]);
			}
			/// if there is next cmd
			if (cmd->next)
			{
//				printf("parent %d [%s] there is next cmd\n", getpid(), cmd->tokens[0]);

				old_fd[1] = fd[1];
				old_fd[0] = fd[0];
			}
			i++;
//			wait_child(pid);

		}
	}
	int status = 0;
//	printf("waitpid %d\n", getpid());
	for (i = 0; i < first_cmd + 1; i++)
		waitpid(pids[i], &status, 0);
	/// if there are multiple cmd
	if (multiple_cmds)
	{
//		printf("[%s] there are multiple : close old_fds\n", cmd->tokens[0]);
		close(old_fd[0]);
		close(old_fd[1]);
	}

	return (0);
}


