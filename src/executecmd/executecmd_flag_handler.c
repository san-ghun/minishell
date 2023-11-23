/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_flag_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:11:08 by sanghupa          #+#    #+#             */
/*   Updated: 2023/11/17 14:12:00 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
