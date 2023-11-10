/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_disptach_handler.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:39:49 by minakim           #+#    #+#             */
/*   Updated: 2023/11/10 16:28:25 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// dispatch struct
typedef struct s_cmd
{
	char	*cmd_name;
	void	(*cmd_func)(t_sent *node, t_elst *lst);
}				t_cmd;

static t_cmd	*builtins(void)
{
	static t_cmd	this[] = {
			{"cd", ft_cd},
			{"unset", ft_unset},
			{"export", ft_export},
			{"exit", ft_exit},
			{"echo", ft_echo},
			{"pwd", ft_pwd},
			{"env", ft_env},
			{NULL, NULL}
	};
	static int		is_init;

	if (is_init)
		return (&(*this));
	is_init = TRUE;
	return (&(*this));
}

int	dispatchcmd(t_sent *cmd, t_cmd *cmd_table, int i)
{
	int		res;

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
		if (ft_strequ(cmd->tokens[0], cmd_table[i].cmd_name)
			&& ft_strequ(cmd->tokens[0], "exit"))
		{
			cmd_table[i].cmd_func(cmd, ms_env());
			return (-1);
		}
		if (ft_strequ(cmd->tokens[0], cmd_table[i].cmd_name))
			return (dispatchcmd(cmd, cmd_table, i));
	}
	return (0);
}

int	is_built_in(t_sent *cmd)
{
	t_cmd	*table;
	int		i;

	table = builtins();
	i = -1;
	while (table[++i].cmd_name)
	{
		if (ft_strequ(cmd->tokens[0], table[i].cmd_name))
			return (1);
	}
	return (0);
}
