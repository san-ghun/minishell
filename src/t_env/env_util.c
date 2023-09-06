/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:14:20 by minakim           #+#    #+#             */
/*   Updated: 2023/09/04 16:45:33 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"


/// 찾는다면 Value를, 찾지 못한다면 NULL을 반환합니다.
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