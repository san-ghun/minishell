/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_disptach_handler.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:39:49 by minakim           #+#    #+#             */
/*   Updated: 2023/10/17 17:50:57 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// TODO : 전부 다시 쓰는게 더 빠를지도 :)
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
	{"exit", ft_exit},
	{NULL, NULL}
	};
	static int		is_init;

	if (is_init)
		return (&(*this));
	is_init = TRUE;
	return (&(*this));
}

int	dispatchcmd(t_sent *cmd, int i)
{
	int		res;
	t_cmd	*cmd_table;

	cmd_table = builtins();
	res = 1;
	g_sigstatus = 1;
	cmd_table[i].cmd_func(cmd, ms_env());
	return (res);
}

int	dispatchcmd_wrapper(t_sent *cmd)
{
	t_cmd	*cmd_table;
	int		i;

	cmd_table = builtins();
	i = -1;
	while (cmd_table[++i].cmd_name)
	{
		if (ft_strequ(cmd->tokens[0], "exit") && ft_strequ(cmd->tokens[0], cmd_table[i].cmd_name))
		{
			cmd_table[i].cmd_func(cmd, ms_env());
			return (-1);
		}
		if (ft_strequ(cmd->tokens[0], cmd_table[i].cmd_name))
			return (dispatchcmd(cmd, i));
	}
	return (0);
}

int	is_built_in(t_sent *cmd)
{
	t_cmd	*cmd_table;
	int		i;

	cmd_table = builtins();
	i = -1;
	while (cmd_table[++i].cmd_name)
	{
		if (ft_strequ(cmd->tokens[0], cmd_table[i].cmd_name))
			return (1);
	}
	return (0);
}
