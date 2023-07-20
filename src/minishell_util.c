/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:21:57 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/20 20:25:57 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	getcmd(char *cmd, int len)
{
	char	*command;

	command = readline("> ");
	ft_strlcpy(cmd, command, len);
	free(command);
}

int	isexit(char *cmd)
{
	return (ft_strncmp(cmd, "exit", 4) == 0);
}
