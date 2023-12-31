/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:38:30 by sanghupa          #+#    #+#             */
/*   Updated: 2023/11/17 17:14:36 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(char *path, char *cmd)
{
	char	command[DATA_SIZE];
	char	*msg;

	if (path == NULL)
	{
		ft_strlcpy(command, cmd, ft_strlen(cmd) + 1);
		msg = ft_strdup(": command not found\n");
		ft_strlcat(command, msg, ft_strlen(command) + ft_strlen(msg) + 1);
		ms_env()->g_exit = 127;
		ms_error(command);
		free(msg);
		return (1);
	}
	return (0);
}

int	check_pid(pid_t pid)
{
	g_sigstatus = 1;
	if (pid < 0)
		return (ms_error("unable to fork\n"));
	return (0);
}

int	check_all_cmd(t_sent *cmd)
{
	t_sent	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		if (tmp->output_flag == PIPE_FLAG && tmp->tokens_len > 0)
		{
			if (ft_strequ(tmp->tokens[0], "|") || \
			(tmp->next && (ft_strequ(tmp->next->tokens[0], "|"))))
			{
				cmd->output_flag = STDERR_FILENO;
				ft_putstr_fd(ONLY_PIPES, 2);
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	is_only_pipe(t_sent *cmd, int total_cmd_count)
{
	if (cmd->tokens[0] == NULL && cmd->output_flag == PIPE_FLAG)
	{
		if (total_cmd_count == 0)
		{
			cmd->output_flag = STDERR_FILENO;
			ft_putstr_fd(ONLY_PIPE, 2);
			return (-1);
		}
		else if (total_cmd_count > 0 && ft_strequ(cmd->next->tokens[0], "|"))
		{
			cmd->output_flag = STDERR_FILENO;
			ft_putstr_fd(ONLY_PIPES, 2);
			return (-1);
		}
	}
	return (check_all_cmd(cmd));
}

int	check_dir(char *cmd, char **path)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, F_OK) == 0)
		{
			tmp = ft_strdup(cmd);
			if (tmp)
			{
				*path = tmp;
				return (1);
			}
		}
	}
	*path = NULL;
	return (-1);
}
