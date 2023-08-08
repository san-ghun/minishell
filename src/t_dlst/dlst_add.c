/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:22:25 by minakim           #+#    #+#             */
/*   Updated: 2023/08/08 13:28:22 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

int	dlst_addfront(t_dlst_data **lst, t_dlst **new_node)
{
	if (*lst == NULL || *new_node == NULL)
		return (0);
	if ((*lst)->begin == NULL)
	{
		(*new_node)->prev = NULL;
		(*new_node)->next = NULL;
		(*lst)->begin = *new_node;
		(*lst)->end = *new_node;
	}
	else
	{
		(*new_node)->next = (*lst)->begin;
		(*lst)->begin->prev = *new_node;
		(*new_node)->prev = NULL;
		(*lst)->begin = *new_node;
	}
	dlst_updatesize(*lst, +1);
	return (1);
}

int	dlst_addrear(t_dlst_data **lst, t_dlst **new_node)
{
	if (*lst == NULL || *new_node == NULL)
		return (0);
	if ((*lst)->end == NULL)
	{
		(*new_node)->prev = NULL;
		(*new_node)->next = NULL;
		(*lst)->begin = *new_node;
		(*lst)->end = *new_node;
	}
	else
	{
		(*lst)->end->next = *new_node;
		(*new_node)->prev = (*lst)->end;
		(*new_node)->next = NULL;
		(*lst)->end = *new_node;
	}
	dlst_updatesize(*lst, +1);
	return (1);
}

int	dlst_addnext(t_dlst_data **lst, t_dlst **current, t_dlst **new_node)
{
	t_dlst	*next;

	if (!*current || !*new_node)
		return (-1);
	if ((*lst)->end == (*current))
		return (dlst_addrear(lst, new_node));
	else
	{
		next = (*current)->next;
		(*current)->next = *new_node;
		(*new_node)->prev = *current;
		(*new_node)->next = next;
		next->prev = (*new_node);
		dlst_updatesize(*lst, +1);
		return (1);
	}
}
