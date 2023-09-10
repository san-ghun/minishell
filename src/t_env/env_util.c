/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:14:20 by minakim           #+#    #+#             */
/*   Updated: 2023/09/10 14:24:39 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

/// 찾는다면 Value를, 찾지 못한다면 NULL을 반환합니다. 이 함수를 통해 lst를 수정해서는 안됩니다.
char	*env_getvalue(t_elst *lst, char *key)
{
	t_env	*node = lst->begin;

	while (node)
	{
		if (ft_strequ(node->key, key))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

void	env_setexit(t_elst *lst, int status)
{
	lst->g_exit = status;
}

/// @param lst env list, it has front node and last node.
/// @param key key of the envp form.
/// @param value value of the envp form.
/// @param overwrite If overwrite is set to 0 (or any other non-true value),
/// then the function does nothing if the variable name already exists.
/// If overwrite is set to a non-zero value (true),
/// then the function sets the variable name to the value value,
/// regardless of whether the variable name already exists.
/// @return return (0) or return error (-1)
int	ft_setenv(t_elst *lst, const char *key, const char *value, int overwrite)
{
	t_env	*node;

	if (!key || !value)
		return (-1);
	node = lst->begin;
	while (node)
	{
		if (ft_strequ(node->key, key))
		{
			if (overwrite)
			{
				free(node->value);
				node->value = ft_strdup(value);
			}
			return (0);
		}
		node = node->next;
	}
	node = NULL;
	node = env_newnode(ft_strdup((char *)key), ft_strdup((char *)value));
	if (!node)
		return (-1);
	env_addrear(&lst, &node);
	return (0);
}