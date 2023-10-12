/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:40:09 by minakim           #+#    #+#             */
/*   Updated: 2023/10/12 12:51:37 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @note
void	ft_unset(t_sent *node, t_elst *lst);

int	ft_unsetenv(char *key, t_elst *lst)
{
	t_env	*tmp;

	tmp = lst->begin;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
		{
			env_delone(lst, tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_unset(t_sent *node, t_elst *lst)
{
	char	*key;
	int		fd;

	fd = redi_out(node);
	key = node->tokens[1];
	ft_unsetenv(key, lst);
	if (fd != 1)
		close(fd);
	lst->g_exit = 0;
}

//void	ft_unset(t_sent *node, t_elst *lst)
//{
//	char	*key;
//	int		fd;
//
//	fd = redi_out(node);
//	if (node->tokens_len == 2)
//	{
//		key = node->tokens[1];
//		if (!ft_unsetenv(key, lst))
//			ft_putstr_fd("\n", fd);
//		if (fd != 1)
//			close(fd);
//		lst->g_exit = 0;
//	}
//	else
//	{
//		ms_error("unset: number of ineligible tokens\n");
//		lst->g_exit = 1;
//	}
//}
