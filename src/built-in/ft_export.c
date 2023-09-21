/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:32:14 by minakim           #+#    #+#             */
/*   Updated: 2023/09/17 20:48:41 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <assert.h> /// 나중에 제거하기 !

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

	if (node->tokens_len < 1)
	{
		assert("error");
		lst->g_exit = 1;
	}
	else if (node->tokens_len == 1)
		ft_env(node, lst);
	else
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
}