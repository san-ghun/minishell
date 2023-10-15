/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:01:20 by sanghupa          #+#    #+#             */
/*   Updated: 2023/10/15 21:27:05 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int fds[2];                      // 2개의 fd를 담을 배열을 정의한다.
	pipe(fds);                       // pipe를 호출해 두 개의 fd로 배열을 채워준다.
	pid_t pid = fork();              // 부모 프로세스의 fd와 메모리를 복제한 자식 프로세스 생성한다.

	if (pid == 0) {                  // if pid == 0, 자식 프로세스
		dup2(fds[0], STDIN_FILENO);    // fds[0]으로 표준입력을 넘겨준다.
		close(fds[0]);                 // fds[0]은 자식 프로세스에서 더이상 필요하지 않기 떄문에 닫아준다. 복사본이기 때문에(?)
		close(fds[1]);                 // 원래부터 필요없었던 fd라 닫아준다.
		char *cmd[] = {(char *)"sort", NULL};   // sort 명령어 인자를 만들어준다.
		if (execvp(cmd[0], cmd) < 0)
			exit(0);  // sort 명령어 실행하고 문제있으면 exit
	}

	// 부모 프로세스 코드 시작
	close(fds[0]);                 // 쓰기만 하면되는 부모 프로세스에서는 필요 없는 fd라 닫아준다.
	const char *words[] = {"pear", "peach", "apple"}; // 자식 프로세스에서 읽을 write input

	for (int i = 0; i < 3; i++) {
		dprintf(fds[1], "%s\n", words[i]); // fds[1]에 출력을 쓴다.
	}
	close(fds[1]);

	int status;
	pid_t wpid = waitpid(pid, &status, 0); // 자식 프로세스가 종료될때까지 기다린다.
	return (wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1);
}


//
//int		run_process(t_sent *cmd, t_elst *lst, int *fd, int *prev_fd);
//int		child_proc(t_sent *cmd, int *fd, int *prev_fd);
//int		parent_proc(int pid, t_sent *cmd, int *fd, int *prev_fd);
//
//int	executecmd(t_deque *deque)
//{
//	int		fd[2];
//	int		prev_fd;
//	int		bt;
//	t_sent	*cmd;
//
//	init_fd(fd, &prev_fd);
//	while (deque->size > 0)
//	{
//		cmd = deque_pop_back(deque);
//		if (cmd->output_flag == PIPE_FLAG)
//			pipe(fd);
//		bt = dispatchcmd_wrapper(cmd, fd, &prev_fd);
//		if (bt < 0)
//			return (-1);
//		if (bt)
//			continue ;
//		if (run_process(cmd, ms_env(), fd, &prev_fd) < 0)
//			return (-1);
//	}
//	return (0);
//}
//
//int	run_process(t_sent *cmd, t_elst *lst, int *fd, int *prev_fd)
//{
//	pid_t	pid;
//	char	**menvp;
//	char	*path;
//
//	menvp = dll_to_envp(lst);
//	path = ms_find_path(cmd->tokens[0]);
//	if (cmd->output_flag == STDERR_FILENO)
//	{
//		ms_error(cmd->output_argv);
//		return (ft_free_check(path, menvp, 1));
//	}
//	if (check_path(path, cmd->tokens[0]))
//		return (ft_free_check(path, menvp, 1));
//	pid = fork();
//	if (check_pid(pid))
//		return (ft_free_check(path, menvp, 1));
//	if (pid == 0)
//	{
//		if (child_proc(cmd, fd, prev_fd) < 0)
//			return (ft_free_check(path, menvp, -1));
//		if (execute_node(cmd, menvp, path) < 0)
//			return (ft_free_check(path, menvp, -1));
//	}
//	lst->g_exit = parent_proc(pid, cmd, fd, prev_fd);
//	return (ft_free_check(path, menvp, 0));
//}
//
//int	child_proc(t_sent *cmd, int *fd, int *prev_fd)
//{
//	if (run_by_flag(cmd, INPUT) < 0)
//		return (-1);
//	if (*prev_fd != -1)
//		dup2(*prev_fd, STDIN_FILENO);
//	if (cmd->output_flag == PIPE_FLAG && fd[1] != -1)
//	{
//		close(fd[0]);
//		dup2(fd[1], STDOUT_FILENO);
//	}
//	if (run_by_flag(cmd, OUTPUT) < 0)
//		return (-1);
//	return (0);
//}
//
//int	parent_proc(int pid, t_sent *cmd, int *fd, int *prev_fd)
//{
//	int	status;
//	int	result;
//
//	result = -1;
//	if (*prev_fd != -1)
//		close(*prev_fd);
//	if (cmd->output_flag == PIPE_FLAG)
//	{
//		close(fd[1]);
//		*prev_fd = fd[0];
//	}
//	if (cmd->next == NULL)
//	{
//		waitpid(pid, &status, 0);
//		if (WIFEXITED(status))
//			result = WEXITSTATUS(status);
//	}
//	return (result);
//}
//
//int	execute_node(t_sent *node, char *menvp[], char *path)
//{
//	size_t	tmp_size;
//	char	**tmp;
//
//	if (node->tokens[0] == NULL || path == NULL)
//		return (-1);
//	if (node->tokens[0][0] == '/')
//	{
//		tmp_size = ms_split_size(node->tokens[0], '/');
//		tmp = (char **)malloc(sizeof(char *) * (tmp_size + 1));
//		tmp = ms_split_process(node->tokens[0], '/', tmp, 0);
//		node->tokens[0] = ft_strdup(tmp[tmp_size - 1]);
//		ft_free_2d(tmp);
//	}
//	execve(path, node->tokens, menvp);
//	ms_error("Failed to execute command\n");
//	return (-1);
//}
//
//==
///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   executecmd.c                                       :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2023/10/15 14:06:17 by minakim           #+#    #+#             */
///*   Updated: 2023/10/15 20:36:14 by minakim          ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "minishell.h"
//
////static int get_numpipe(t_sent *cmd)
////{
////	int	numpipe;
////
////	numpipe = 0;
////	while (cmd)
////	{
////		if (cmd->output_flag == PIPE_FLAG)
////			numpipe++;
////		cmd = cmd->next;
////	}
////	return (numpipe);
////}
//
//int	execute_node(t_sent *node, char *menvp[], char *path)
//{
//	size_t	tmp_size;
//	char	**tmp;
//
//	if (node->tokens[0] == NULL || path == NULL)
//		return (-1);
//	if (node->tokens[0][0] == '/')
//	{
//		tmp_size = ms_split_size(node->tokens[0], '/');
//		tmp = (char **)malloc(sizeof(char *) * (tmp_size + 1));
//		tmp = ms_split_process(node->tokens[0], '/', tmp, 0);
//		node->tokens[0] = ft_strdup(tmp[tmp_size - 1]);
//		ft_free_2d(tmp);
//	}
//	execve(path, node->tokens, menvp);
//	ms_error("Failed to execute command\n");
//	return (-1);
//}
//
////void	close_all_pipe(t_deque *deque)
////{
////	t_sent	*cmd;
////
////	cmd = deque->end;
////	while (cmd)
////	{
////		if (cmd->output_flag == PIPE_FLAG)
////		{
////			printf("parent %d close: fd[%d]\n", getpid(), cmd->fd[0]);
////			close(cmd->fd[0]);
////
////			printf("parent %d close: fd[%d]\n", getpid(), cmd->fd[1]);
////			close(cmd->fd[1]);
////		}
////		cmd = cmd->next;
////	}
////}
//
//int	ft_execvp(t_sent *cmd)
//{
//	char	**menvp;
//	char	*path;
//	int		bt;
//
//	bt = -1;
//	menvp = dll_to_envp(ms_env());
//	path = ms_find_path(cmd->tokens[0]);
//	if (cmd->output_flag == STDERR_FILENO)
//	{
//		ms_error(cmd->output_argv);
//		return (ft_free_check(path, menvp, 1));
//	}
//	if (check_path(path, cmd->tokens[0]))
//		return (ft_free_check(path, menvp, 1));
//	bt = dispatchcmd_wrapper(cmd);
//	if (bt < 0)
//		return (-1);
//	if (bt == 0)
//		if (execute_node(cmd, menvp, path) < 0)
//			return (ft_free_check(path, menvp, -1));
//	return (ft_free_check(path, menvp, 0));
//}
//
//int	wait_child(int pid)
//{
//	int status;
//	int	res;
//	t_elst	*lst;
//
//	status = 0;
//	res = 0;
//	lst = ms_env();
//	waitpid(pid, &status, 0);
//	if (WIFSIGNALED(status) && lst->g_exit != 130)
//		res = WTERMSIG(status);
//	else if (WIFEXITED(status) && lst->g_exit != 130)
//		res = WEXITSTATUS(status);
//	else if (WIFSTOPPED(status) && lst->g_exit != 130)
//		res = 1;
//	return (res);
//}
//
/////	If it's not the first command,
///// the child's standard input is replaced with the read end of the previous pipe.
///// If it's not the last command,
///// the child's standard output is replaced with the write end of the current pipe.
//
//#define READ 0
//#define WRITE 1
//int	executecmd(t_deque *deque)
//{
//	t_sent	*cmd;
//	t_sent	*first;
//	t_sent	*last;
//	int		pid;
//	int 	c_fd[2];
//	int		p_fd[2];
//	int		size_backup;
//
//	size_backup = deque->size;
//	if (deque->size == 0)
//		return (0);
//	cmd = deque->end;
//	first = deque->end;
//	last = deque->begin;
//	c_fd[0] = -1;
//	c_fd[1] = -1;
//	p_fd[0] = -1;
//	p_fd[1] = -1;
//	while (deque->size > 0)
//	{
//		cmd = deque_pop_back(deque);
//		pid = fork();
//		if( pid < 0 )
//		{
//			perror("fork()");
//			return (-1);
//		}
//		else if (pid == 0) /// child process
//		{
//			/// call redirection
//			if (run_by_flag(cmd, INPUT) < 0)
//				return (-1);
//			if (run_by_flag(cmd, OUTPUT) < 0)
//				return (-1);
//			if (cmd->output_flag == PIPE_FLAG)
//				pipe(c_fd);
//			/* child gets input from the previous command,
//            if it's not the first command */
//			if (cmd != first)
//			{
//				printf("[%s] child `%d` dup2: prev fd[%d] to IN(0) | NOT FIRST\n", cmd->tokens[0], getpid(), p_fd[0]);
//				dup2(p_fd[0], STDIN_FILENO);
//				printf("[%s] child `%d` close: prev fd[%d] | NOT FIRST\n", cmd->tokens[0], getpid(), p_fd[0]);
//				close(p_fd[0]);
//				printf("[%s] child `%d` close: prev fd[%d] | NOT FIRST\n", cmd->tokens[0], getpid(), p_fd[1]);
//				close(p_fd[1]);
//			}
//			/* child outputs to next command,
//			 if it's not the last command */
//			if (cmd != last)
//			{
//				printf("[%s] child `%d` close: fd[%d] | NOT LAST\n", cmd->tokens[0], getpid(), c_fd[0]);
//				close(c_fd[0]);
//				printf("[%s] child `%d` dup2: fd[%d] to OUT(1) | NOT LAST\n", cmd->tokens[0], getpid(), c_fd[1]);
//				dup2(c_fd[1], STDOUT_FILENO);
//				printf("[%s] child `%d` close: fd[%d] | NOT LAST\n", cmd->tokens[0], getpid(), c_fd[1]);
//				close(c_fd[1]);
//			}
//
//			///		execvp : built-in && execvp || die
//			if (ft_execvp(cmd) < 0)
//				return (-1);
//		}
//		else
//		{
//			wait_child(pid);
//			if (/* there is a previous cmd */ cmd != first)
//			{
//				printf("[%s] parent %d close: prev fd[%d] | NOT FIRST\n", cmd->tokens[0], getpid(), p_fd[0]);
//				printf("[%s] parent %d close: prev fd[%d]| NOT FIRST\n", cmd->tokens[0], getpid(), p_fd[1]);
//				close(p_fd[0]);
//				close(p_fd[1]);
//			}
//			if ( /* there is a next cmd */ cmd != last)
//			{
//				printf("[%s] parent %d prev fd[%d] = current fd[%d]  | NOT LAST\n", cmd->tokens[0], getpid(), p_fd[0], c_fd[0]);
//				printf("[%s] parent %d prev fd[%d] = current fd[%d]  | NOT LAST\n", cmd->tokens[0], getpid(), p_fd[1], c_fd[1]);
//				p_fd[0] = c_fd[0];
//				p_fd[1] = c_fd[1];
//			}
////			wait_child(pid);
////			close_all_pipe(deque);
//		}
//	}
//	if (size_backup > 1)
//	{
//		close(p_fd[0]);
//		close(p_fd[1]);
//	}
//	return (0);
//}
//
//
