/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:21:57 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/18 16:26:43 by sanghupa         ###   ########.fr       */
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
