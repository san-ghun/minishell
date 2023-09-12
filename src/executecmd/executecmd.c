/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:01:20 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/13 01:14:00 by minakim          ###   ########.fr       */
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

void	execute_node(t_sent *node, t_elst *lst)
{
	pid_t	pid;
	char	**menvp;

	pid = fork();
	if (pid < 0)
	{
		perror("Error");
		ft_putstr_fd("Failed to fork\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (node->tokens[0] == NULL)
			exit(EXIT_SUCCESS);
		if (dispatchcmd(node, lst))
			exit(EXIT_SUCCESS);
		menvp = dll_to_envp(lst);
		ft_exec(node->tokens, menvp);
		ft_free_2d(menvp);
		perror("Error");
		ft_putstr_fd("Failed to execute command\n", 2);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
}

typedef enum {
	NONE,
	INPUT,
	OUTPUT
} e_flag;

typedef struct s_exe {
	int		flag;
	e_flag	type;
	void	(*cmd_func)(t_sent *node, t_elst *lst);
}			t_exe;

void	executecmd(t_deque *deque, t_elst *lst)
{
	t_sent	*node;
	int		i;
	t_exe	exe_f[] = {
			{HDOC_FLAG, INPUT, execute_heredoc},
			{REDI_RD_FLAG, INPUT, execute_redi_read},
			{PIPE_FLAG, INPUT, execute_pipe_input},
			{PIPE_FLAG, OUTPUT, execute_pipe_output},
			{REDI_WR_APPEND_FLAG, OUTPUT, execute_redi_append},
			{REDI_WR_TRUNC_FLAG, OUTPUT, execute_redi_trunc},
			{-1, NONE, NULL}
	};
	i = -1;
	while (0 < deque->size)
	{
		node = deque_pop_back(deque);
		while (exe_f[++i].cmd_func != NULL)
		{
			if (node->input_flag == exe_f[i].flag && exe_f[i].type == INPUT)
				exe_f[i].cmd_func(node, lst);
			else if (node->output_flag == exe_f[i].flag && exe_f[i].type == OUTPUT)
				exe_f[i].cmd_func(node, lst);
		}
	}
	return ;
}