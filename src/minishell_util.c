/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:21:57 by sanghupa          #+#    #+#             */
/*   Updated: 2023/10/14 17:19:54 by minakim          ###   ########.fr       */
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

void	handle_sigchld(int sig)
{
	int	saved_errno;

	(void)sig;
	saved_errno = errno;
	while (waitpid((pid_t)(-1), 0, WNOHANG) > 0)
	{
	}
	errno = saved_errno;
}

void	sigchld(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigchld;
	sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
	sigaction(SIGCHLD, &sa, NULL);
}
