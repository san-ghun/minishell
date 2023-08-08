/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:22:59 by minakim           #+#    #+#             */
/*   Updated: 2023/08/08 15:22:59 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

int	dlst_del(t_dlst *node_to_delete)
{
	free(node_to_delete->cnt);
	node_to_delete->prev = NULL;
	node_to_delete->next = NULL;
}

int	dlst_delone(t_dlst_data *list, t_dlst *node_to_delete)
{
	if (list == NULL || node_to_delete == NULL)
		return (0);
	if (list->begin == node_to_delete)
	{
		list->begin = node_to_delete->prev;
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
	dlst_del(node_to_delete);
	free(node_to_delete);
	dlst_updatesize(list, -1);
	return (1);
}

void	dlst_dellst(t_dlst_data *lst)
{
	while (lst->end != NULL)
		dlst_delone(lst, lst->end);
	free(lst);
}
