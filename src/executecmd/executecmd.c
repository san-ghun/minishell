/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:06:17 by minakim           #+#    #+#             */
/*   Updated: 2023/11/10 01:49:25 by minakim          ###   ########.fr       */
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
	t_sent		*cmd;
	static int	bt = 0;
	t_ctx		*c;
	c = ms_ctx();
	c->cmd_count = deque->size - 1;
	c->first_cmd = 0;
	while (deque->size > 0 && c->i < MAX_PIPES)
	{
		cmd = deque_pop_back(deque);
		if (cmd->next && cmd->output_flag == PIPE_FLAG)
		{
			if (c->cmd_count == deque->size)
				c->first_cmd = 1;
			pipe(c->fd);
			printf("this 1 msgs happens in main process [%s][%d]\n", cmd->tokens[0], getpid());
			printf("Pipe created with FDs: read end = %d, write end = %d\n", c->fd[0], c->fd[1]);
		}
		if (is_built_in(cmd) == CHILD)
		{
			if (run_process(cmd, deque) < 0)
				return (-1);
		}
		else
		{
			/// 아이디어 : 여러 커맨드가 있고, 첫번째 커맨드가 "builtin"이라면
			/// c에 체크하고, "<<< here " 실행하지 않음. 보통의 경우는 parent에서 닫아버리자.
			bt = dispatchcmd_wrapper(cmd, PARENT);
			if (bt < 0)
				return (bt);
			continue ;
		}
	}
	return (wait_child(c, c->old_fd, c->wait_count));
}

int	ft_execvp(t_sent *cmd)
{
	char	**menvp;
	char	*path;

	if (!cmd->tokens[0])
		return (1);
	else if (cmd->tokens[0][0] == '|')
	{
		cmd->output_flag = STDERR_FILENO;
		cmd->output_argv = \
			ft_strdup("syntax error: near unexpected token `|`\n");
	}
	if (cmd->output_flag == STDERR_FILENO)
		return (ft_putstr_fd(cmd->output_argv, 2), 1);
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
	signal(SIGQUIT, SIG_DFL);
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
	if (c->cmd_count && c->first_cmd != 1) /// <<< here
	{

		printf("this 2 msgs happens in main process [%d]\n", getpid());
		close(old_fd[0]);
		printf("Closed FD %d (last cmd)\n", old_fd[0]);
		close(old_fd[1]);
		printf("Closed FD %d (last cmd)\n", old_fd[1]);
	}
	if (WIFSIGNALED(status) && ms_env()->g_exit != 130)
		res = WTERMSIG(status);
	else if (WIFEXITED(status) && ms_env()->g_exit != 130)
		res = WEXITSTATUS(status);
	else if (WIFSTOPPED(status) && ms_env()->g_exit != 130)
		res = 1;
	ms_env()->g_exit = res;
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
