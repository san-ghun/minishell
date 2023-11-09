/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:31:26 by sanghupa          #+#    #+#             */
/*   Updated: 2023/10/04 14:55:27 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_sent *node, t_elst *lst)
{
	static char	pwd[DATA_SIZE];
	int			fd;

	fd = redi_out(node);
	if (getcwd(pwd, DATA_SIZE))
	{
		ft_putendl_fd(pwd, fd);
		lst->g_exit = 0;
	}
	else
	{
		lst->g_exit = 1;
		ms_error("미쉘: pwd: error retrieving current directory\n");
	}
	if (fd != 1)
		close(fd);
}
