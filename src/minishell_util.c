/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:21:57 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/24 14:26:30 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	getcmd(char *cmd, size_t len)
{
	char	*command;

	command = readline("> ");
	if (!command)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	len = ft_strlen(command);
	if (len > MAX_COMMAND_LEN)
		ft_putstr_fd("warn: command exceed MAX_COMMAND_LEN\n", 2);
	ft_strlcpy(cmd, command, len + 1);
	free(command);
}

int	isexit(char *cmd)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(cmd, "exit", 4) == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ret = 1;
	}
	return (ret);
}
