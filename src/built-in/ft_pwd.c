/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:31:26 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/23 16:34:06 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_sent *node, t_elst *lst)
{
	static char	pwd[DATA_SIZE];
	int			fd;

	fd = redi_out(node);
	if (node->tokens_len > 1)
	{
		ft_printf("error\n");
		lst->g_exit = 1; // tmp error status
		return ;
	}
	else if (getcwd(pwd, DATA_SIZE))
	{
		ft_putendl_fd(pwd, fd);
		lst->g_exit = 0;
	}
	else
	{
		ft_printf("pwd: error retrieving current directory\n");
		lst->g_exit = 1; // tmp error status
	}
	if (fd != 1)
		close(fd);
}
