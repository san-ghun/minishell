/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:38:30 by sanghupa          #+#    #+#             */
/*   Updated: 2023/11/17 15:49:11 by minakim          ###   ########.fr       */
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

int	is_only_pipe(t_sent *cmd, int total_cmd_count)
{
	if (cmd->tokens[0] == NULL && cmd->output_flag == PIPE_FLAG)
	{
		if (total_cmd_count == 0)
		{
			cmd->output_flag = STDERR_FILENO;
			cmd->output_argv = ft_strdup(ONLY_PIPE);
			ft_putstr_fd(cmd->output_argv, 2);
			return (-1);
		}
		else if (total_cmd_count > 0 && ft_strequ(cmd->next->tokens[0], "|"))
		{
			cmd->output_flag = STDERR_FILENO;
			cmd->output_argv = ft_strdup(ONLY_PIPES);
			ft_putstr_fd(cmd->output_argv, 2);
			return (-1);
		}
	}
	return (0);
}

int	check_pwd(char *cmd, char **path)
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
