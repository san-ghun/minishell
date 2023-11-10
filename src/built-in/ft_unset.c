/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:40:09 by minakim           #+#    #+#             */
/*   Updated: 2023/11/10 17:25:23 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @note

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
	int		i;

	i = 1;
	fd = redi_out(node);
	if (node->tokens_len > 1)
	{
		while (node->tokens[i])
		{
			key = node->tokens[i];
			ft_unsetenv(key, lst);
			i++;
		}
	}
	if (fd != 1)
		close(fd);
	lst->g_exit = 0;
}
