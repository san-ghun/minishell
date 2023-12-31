/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:11:49 by minakim           #+#    #+#             */
/*   Updated: 2023/09/28 22:57:25 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This DLL stores the start and end nodes separately in t_elst lst,
/// and lst updates size, which is the total number of nodes.
void	env_updatesize(t_elst *lst, int add)
{
	if ((lst)->size < 0)
		(lst)->size = -1;
	(lst)->size += add;
}

/// @note Parameters key and value must be malloc
/// This DLL function is built on the premise that 
/// the key and value will be allocated.
/// will free both key and value from env_del.
t_env	*env_newnode(char *key, char *value)
{
	t_env	*new;

	if (!key || !value)
		return (NULL);
	new = ft_memalloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/// @note t_elst lst requires memory allocation
/// this function is called from the env_to_dll function in src/built-in/ft_env,
/// and is not used separately.
t_elst	*env_init(void)
{
	t_elst	*data;

	data = (t_elst *) ft_memalloc(sizeof(t_elst));
	data->begin = NULL;
	data->end = NULL;
	data->size = 0;
	data->g_exit = 0;
	return (data);
}

t_elst	*ms_env(void)
{
	static t_elst	this;
	static int		is_init;

	if (is_init)
		return (&this);
	this = (t_elst){
		.begin = NULL,
		.end = NULL,
		.size = 0,
		.g_exit = 0,
	};
	is_init = TRUE;
	return (&this);
}
