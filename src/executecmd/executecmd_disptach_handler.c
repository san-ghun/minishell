/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_disptach_handler.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:39:49 by minakim           #+#    #+#             */
/*   Updated: 2023/10/20 12:57:18 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// TODO : 전부 다시 쓰는게 더 빠를지도 :)
typedef struct s_cmd
{
	char	*cmd_name;
	void	(*cmd_func)(t_sent *node, t_elst *lst);
}				t_cmd;

static t_cmd	*builtins_child(void)
{
	static t_cmd	this[] = {
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

static t_cmd	*builtins_parent(void)
{
	static t_cmd	this[] = {
			{"cd", ft_cd},
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

t_cmd	*set_cmd_table(int where)
{
	t_cmd	*cmd_table;

	cmd_table = NULL;
	if (where == CHILD)
		cmd_table = builtins_child();
	else if (where == PARENT)
		cmd_table = builtins_parent();
	return (cmd_table);
}


int	dispatchcmd(t_sent *cmd, int i, int where)
{
	int		res;
	t_cmd	*cmd_table;

	cmd_table = set_cmd_table(where);
	res = 1;
	g_sigstatus = 1;
	cmd_table[i].cmd_func(cmd, ms_env());
	return (res);
}

int	dispatchcmd_wrapper(t_sent *cmd, int where)
{
	t_cmd	*cmd_table;
	int		i;

	cmd_table = set_cmd_table(where);
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
			return (dispatchcmd(cmd, i, where));
	}
	return (0);
}

int	is_built_in(t_sent *cmd)
{
	t_cmd	*child;
	t_cmd	*parent;
	int		i;

	child = builtins_child();
	i = -1;
	while (child[++i].cmd_name)
	{
		if (ft_strequ(cmd->tokens[0], child[i].cmd_name))
			return (1);
	}
	parent = builtins_parent();
	i = -1;
	while (parent[++i].cmd_name)
	{
		if (ft_strequ(cmd->tokens[0], parent[i].cmd_name))
			return (2);
	}
	return (0);
}
