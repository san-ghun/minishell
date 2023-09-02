/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:22:25 by minakim           #+#    #+#             */
/*   Updated: 2023/09/02 11:18:55 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

int	env_addfront(t_elst **lst, t_env **new_node)
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
	env_updatesize(*lst, +1);
	return (1);
}

int	env_addrear(t_elst **lst, t_env **new_node)
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
	env_updatesize(*lst, +1);
	return (1);
}

int	env_addnext(t_elst **lst, t_env **current, t_env **new_node)
{
	t_env	*next;

	if (!*current || !*new_node)
		return (-1);
	if ((*lst)->end == (*current))
		return (env_addrear(lst, new_node));
	else
	{
		next = (*current)->next;
		(*current)->next = *new_node;
		(*new_node)->prev = *current;
		(*new_node)->next = next;
		next->prev = (*new_node);
		env_updatesize(*lst, +1);
		return (1);
	}
}

void	env_add_or_update(t_elst *lst, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = lst->begin;
	while (current)
	{
		if (ft_strequ(current->key, key))
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_node = env_newnode(key, value);
	env_addrear(&lst, &new_node);
}
