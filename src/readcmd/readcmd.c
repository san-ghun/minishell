/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:48:32 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/22 22:24:11 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	getcmd(char *cmd, size_t len, int debug_mode)
{
	char	*command;

	if (debug_mode)
		command = readline("미쉘(debug)> ");
	else
		command = readline("미쉘> ");
	if (!command)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (-1);
	}
	len = ft_strlen(command);
	if (len > MAX_COMMAND_LEN)
		ft_putstr_fd("warn: command exceed MAX_COMMAND_LEN\n", 2);
	ft_strlcpy(cmd, command, len + 1);
	if (ft_strncmp(command, "", 1))
		add_history(command);
	free(command);
	return (0);
}

static int	looper_readcmd(char *cmd, char *temp_cmd, size_t *total_len)
{
	size_t	len;

	len = 0;
	len = ft_strcspn(temp_cmd, "\n");
	if (len + *total_len > MAX_COMMAND_LEN)
		return (-1);
	if (len == 0 || temp_cmd[len - 1] != '\\')
	{
		ft_strlcat(cmd, temp_cmd, *total_len + len + 1);
		*total_len += len;
		return (0);
	}
	ft_strlcat(cmd, temp_cmd, *total_len + len);
	*total_len += len;
	return (1);
}

size_t	readcmd(char *cmd, int debug_mode)
{
	int		looper;
	size_t	total_len;
	char	temp_cmd[MAX_COMMAND_LEN];

	ft_bzero(cmd, MAX_COMMAND_LEN);
	looper = 1;
	total_len = 0;
	if (*cmd != '\0')
		return (-1);
	while (looper)
	{
		if (getcmd(temp_cmd, 0, debug_mode) < 0)
			return (-1);
		looper = looper_readcmd(cmd, temp_cmd, &total_len);
	}
	if (looper < 0)
		return (-1);
	cmd[total_len] = '\0';
	return (total_len);
}
