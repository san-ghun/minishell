/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:32:14 by minakim           #+#    #+#             */
/*   Updated: 2023/09/23 16:26:12 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <assert.h> /// 나중에 제거하기 !

/// @note
void	ft_export(t_sent *node, t_elst *lst);

t_env	*env_newnode_split(char *str, char *delim)
{
	char	*separator;
	t_env	*node;

	separator = NULL;
	separator = ft_strpbrk(str, delim);
	if (separator)
	{
		node = env_newnode(ft_substr(str, 0, separator - str), \
			ft_strdup(separator + 1));
	}
	else
		return (NULL);
	return (node);
}

void	ft_export(t_sent *node, t_elst *lst)
{
	t_env	*new;

	if (node->tokens_len == 1)
		ft_env(node, lst);
	else if (node->tokens_len > 1)
	{
		new = env_newnode_split(node->tokens[1], "=");
		if (new)
		{
			env_addrear(&lst, &new);
			lst->g_exit = 0;
		}
		else
		{
			assert("error");
			lst->g_exit = 1;
		}
	}
	else
	{
		assert("error");
		lst->g_exit = 1;
	}
}
