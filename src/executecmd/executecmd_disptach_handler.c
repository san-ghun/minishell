/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_disptach_handler.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:39:49 by minakim           #+#    #+#             */
/*   Updated: 2023/10/17 02:30:18 by minakim          ###   ########.fr       */
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

	printf("ft_exit is set to: %p\n", this[6].cmd_func);
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
		if (ft_strequ(cmd->tokens[0], "exit"))
		{
			printf("cmd_func is set to: %p\n", cmd_table[i].cmd_func);
			printf("pid %d yes. exit\n", getpid());
			if (cmd_table[i].cmd_func == ft_exit) {
				printf("cmd_func is pointing to ft_exit\n");
			}
			cmd_table[i].cmd_func(cmd, ms_env());
			printf("run. exit\n");
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
