/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:38:30 by sanghupa          #+#    #+#             */
/*   Updated: 2023/10/04 22:41:05 by sanghupa         ###   ########.fr       */
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
