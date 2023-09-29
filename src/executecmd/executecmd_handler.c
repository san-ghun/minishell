/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:39:49 by minakim           #+#    #+#             */
/*   Updated: 2023/09/29 22:54:14 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cmd
{
	char	*cmd_name;
	void	(*cmd_func)(t_sent *node, t_elst *lst);
}				t_cmd;

static t_cmd	*builtins(void)
{
	static t_cmd	this[] = {
	{"cd", ft_cd},
	{"echo", ft_echo},
	{"pwd", ft_pwd},
	{"env", ft_env},
	{"unset", ft_unset},
	{"export", ft_export},
	{NULL, NULL}
	};
	static int		is_init;

	if (is_init)
		return (&(*this));
	is_init = TRUE;
	return (&(*this));
}

int	dispatch_err(t_sent *node)
{
	ms_error(node->output_argv);
	return (-1);
}

int	dispatchcmd(t_sent *node, int *fd, int *prev_fd)
{
	t_cmd	*cmd_table;
	int		i;
	pid_t	pid;

	cmd_table = builtins();
	i = -1;
	while (cmd_table[++i].cmd_name)
	{
		if (ft_strequ(node->tokens[0], cmd_table[i].cmd_name))
		{
			if (node->output_flag == STDERR_FILENO)
				return (dispatch_err(node));
			if (cmd_table[i].cmd_name == "cd" || \
				cmd_table[i].cmd_name == "unset" || \
				cmd_table[i].cmd_name == "export")
			{
				cmd_table[i].cmd_func(node, ms_env());
				return (1);
			}
			pid = fork();
			if (pid == 0)
			{
				if (child_proc(node, fd, prev_fd) < 0)
					return (-1);
				cmd_table[i].cmd_func(node, ms_env());
				return (-1);
			}
			parent_proc(pid, node, fd, prev_fd);
			return (1);
		}
	}
	return (0);
}

typedef struct s_exe {
	int		flag;
	t_mode	type;
	int		(*cmd_func)(t_sent *node, t_elst *lst);
}			t_exe;

static int	compare_flags(t_sent *cmd, int current_flag, t_mode flag_type)
{
	if (flag_type == INPUT)
		return (cmd->input_flag == current_flag);
	else if (flag_type == OUTPUT)
		return (cmd->output_flag == current_flag);
	return (0);
}

int	run_by_flag(t_sent *cmd, t_mode flag)
{
	static t_exe	exe_f[] = {
	{HDOC_FLAG, INPUT, flag_heredoc},
	{REDI_RD_FLAG, INPUT, flag_redi_read},
	{REDI_WR_APPEND_FLAG, OUTPUT, flag_redi_append},
	{REDI_WR_TRUNC_FLAG, OUTPUT, flag_redi_trunc},
	{-1, NONE, NULL}
	};
	int				i;

	i = 0;
	while (exe_f[i].cmd_func != NULL)
	{
		if (flag == exe_f[i].type && compare_flags(cmd, exe_f[i].flag, flag))
			return (exe_f[i].cmd_func(cmd, ms_env()));
		i++;
	}
	return (0);
}
