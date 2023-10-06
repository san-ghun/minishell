/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:21:57 by sanghupa          #+#    #+#             */
/*   Updated: 2023/10/06 15:55:42 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isexit(char *cmd)
{
	int	ret;

	ret = 0;
	if (ft_strlen(cmd) == ft_strlen("exit") && ft_strnequ(cmd, "exit", 4))
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ret = 1;
	}
	return (ret);
}

int	ms_error(char *msg)
{
	perror("Error");
	ft_putstr_fd(msg, 2);
	return (1);
}
