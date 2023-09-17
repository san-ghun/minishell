/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:01:20 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/17 13:12:28 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cmd
{
	char	*cmd_name;
	void	(*cmd_func)(t_sent *node, t_elst *lst);
}				t_cmd;

static int	dispatchcmd(t_sent *node, t_elst *lst)
{
	static t_cmd	cmd_table[] = {
			{"cd", ft_cd},
			{"echo", ft_echo},
			{"pwd", ft_pwd},
			{"env", ft_env},
			//	{}, // TODO: unset
			{"export", ft_export},
			{NULL, NULL}
	};
	int				i;

	i = -1;
	while (cmd_table[++i].cmd_name)
	{
		if (ft_strequ(node->tokens[0], cmd_table[i].cmd_name))
		{
			cmd_table[i].cmd_func(node, lst);
			return (1);
		}
	}
	return (0);
}

void	execute_node(t_sent *cmd, t_elst *lst, char **menvp)
{
	if (cmd->tokens[0] == NULL)
		return;
	(void) lst;
	ft_exec(cmd->tokens, menvp);
	perror("Error");
	ft_putstr_fd("Failed to execute command\n", 2);
	exit(EXIT_FAILURE);
}

typedef enum {
	NONE,
	INPUT,
	OUTPUT
}		e_flag;

typedef struct s_exe {
	int		flag;
	e_flag	type;
	void	(*cmd_func)(t_sent *node, t_elst *lst);
}			t_exe;

void	execute_flag(t_sent *cmd, t_elst *lst, e_flag flag)
{
	static t_exe exe_f[] = {
			{HDOC_FLAG,           INPUT,  execute_heredoc},
			{REDI_RD_FLAG,        INPUT,  execute_redi_read},
			{REDI_WR_APPEND_FLAG, OUTPUT, execute_redi_append},
			{REDI_WR_TRUNC_FLAG,  OUTPUT, execute_redi_trunc},
			{-1,                  NONE, NULL}
	};
	int i;

	i = 0;
	while (exe_f[i].cmd_func != NULL)
	{
		if (flag == INPUT)
		{
			if (cmd->input_flag == exe_f[i].flag)
			{
				exe_f[i].cmd_func(cmd, lst);
				break;
			}
			i++;
		}
		else if (flag == OUTPUT)
		{
			if (cmd->input_flag == exe_f[i].flag)
			{
				exe_f[i].cmd_func(cmd, lst);
				break;
			}
			i++;
		}
	}
}

void executecmd(t_deque *deque, t_elst *lst)
{
	int fd[2] = {-1, -1};
	int prev_fd;
	char	**menvp;
	pid_t pid;
	t_sent *cmd;


	prev_fd = -1;
	while (deque->size > 0)
	{
		cmd = deque->end;
		if (cmd->output_flag == PIPE_FLAG)
			pipe(fd);
		if (dispatchcmd(cmd, lst))
			return;
		pid = fork();
		if (pid < 0)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execute_flag(cmd, lst, INPUT);
			if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);
			if (cmd->output_flag == PIPE_FLAG && fd[1] != -1)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
			}
			execute_flag(cmd, lst, OUTPUT);
			menvp = dll_to_envp(lst);
			execute_node(cmd, lst, menvp);
			ft_free_2d(menvp);
			exit(0);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->output_flag == PIPE_FLAG)
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
			waitpid(pid, NULL, 0);
		}
		deque_pop_back(deque);
	}
}