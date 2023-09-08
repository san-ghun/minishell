/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:22:59 by minakim           #+#    #+#             */
/*   Updated: 2023/09/04 15:58:02 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

void	env_del(t_env *target)
{
	target->prev = NULL;
	target->next = NULL;
	free(target->key);
	free(target->value);
	free(target);
}

void	env_delone(t_elst *lst, t_env *target)
{
	if (lst == NULL || target == NULL)
		return ;
	if (lst->begin == target)
	{
		lst->begin = target->next;
		if (lst->begin != NULL)
			lst->begin->prev = NULL;
	}
	if (lst->end == target)
	{
		lst->end = target->prev;
		if (lst->end != NULL)
			lst->end->next = NULL;
	}
	if (target->next != NULL)
		target->next->prev = target->prev;
	if (target->prev != NULL)
		target->prev->next = target->next;
	env_del(target);
	env_updatesize(lst, -1);
	return ;
}

void	env_dellst(t_elst *lst)
{
	t_env	*current;
	t_env	*next_node;

	if (!lst)
		return ;
	current = lst->begin;
	while (current != NULL)
	{
		next_node = current->next;
		env_delone(lst ,current);
		current = next_node;
	}
	lst->g_exit = 0;
	free(lst);
}