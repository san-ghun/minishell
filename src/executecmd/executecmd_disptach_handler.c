/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_disptach_handler.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:39:49 by minakim           #+#    #+#             */
/*   Updated: 2023/10/17 00:54:51 by minakim          ###   ########.fr       */
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
	{"exit", ft_exit},
	{NULL, NULL}
	};
	static int		is_init;

//	printf("call built-in\n");
	if (is_init)
		return (&(*this));
	is_init = TRUE;
	return (&(*this));
}
//
int	dispatch_err(t_sent *node)
{
	ms_error(node->output_argv);
	return (-1);
}

int	dispatch_run_cmd(t_sent *node, int ctab_i, t_cmd *cmd_tab)
{
	if (ft_strequ(cmd_tab[ctab_i].cmd_name, "exit"))
	{
		cmd_tab[ctab_i].cmd_func(node, ms_env());
		return (-1);
	}
	if (ft_strequ(cmd_tab[ctab_i].cmd_name, "cd") || \
		ft_strequ(cmd_tab[ctab_i].cmd_name, "unset") || \
		ft_strequ(cmd_tab[ctab_i].cmd_name, "export"))
	{
		cmd_tab[ctab_i].cmd_func(node, ms_env());
		return (1);
	}
	return (0);
}

int	dispatchcmd(t_sent *node, int ctab_i)
{
	int		res;
	t_cmd	*cmd_tab;

	res = 1;
	cmd_tab = builtins();
	res = dispatch_run_cmd(node, ctab_i, cmd_tab);
	g_sigstatus = 1;
	cmd_tab[ctab_i].cmd_func(node, ms_env());
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
