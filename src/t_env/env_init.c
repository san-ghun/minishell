/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:11:49 by minakim           #+#    #+#             */
/*   Updated: 2023/08/14 19:44:57 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

void	env_updatesize(t_elst *lst, int add)
{
	if ((lst)->size < 0)
		(lst)->size = -1;
	(lst)->size += add;
}

t_env	*env_newnode(char *key, char *value)
{
	t_env	*new;

	if (!key || !value)
		return (NULL);
	new = ft_memalloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_elst	*env_initdll(void)
{
	t_elst	*data;

	data = (t_elst *) ft_memalloc(sizeof(t_elst));
	data->begin = NULL;
	data->end = NULL;
	data->size = 0;
	return (data);
}
