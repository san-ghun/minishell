/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:22:59 by minakim           #+#    #+#             */
/*   Updated: 2023/08/14 17:15:20 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

int	env_reset_node(t_env *node_to_delete)
{
	free(node_to_delete->key);
	free(node_to_delete->value);
	node_to_delete->prev = NULL;
	node_to_delete->next = NULL;
	return (1);
}

int	env_delone(t_elst *list, t_env *node_to_delete)
{
	if (list == NULL || node_to_delete == NULL)
		return (0);
	if (list->begin == node_to_delete)
	{
		list->begin = node_to_delete->next;
		if (list->begin != NULL)
			list->begin->prev = NULL;
	}
	if (list->end == node_to_delete)
	{
		list->end = node_to_delete->prev;
		if (list->end != NULL)
			list->end->next = NULL;
	}
	if (node_to_delete->next != NULL)
		node_to_delete->next->prev = node_to_delete->prev;
	if (node_to_delete->prev != NULL)
		node_to_delete->prev->next = node_to_delete->next;
	env_reset_node(node_to_delete);
	free(node_to_delete);
	env_updatesize(list, -1);
	return (1);
}

void	env_dellst(t_elst *lst)
{
	while (lst->end != NULL)
		env_delone(lst, lst->end);
	free(lst);
}
