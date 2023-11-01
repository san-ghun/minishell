/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_disptach_handler_util.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:38:49 by minakim           #+#    #+#             */
/*   Updated: 2023/10/22 11:43:48 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*builtins_child(void)
{
	static t_cmd	this[] = {
	{"echo", ft_echo},
	{"pwd", ft_pwd},
	{"env", ft_env},
	{NULL, NULL}
	};
	static int		is_init;

	if (is_init)
		return (&(*this));
	is_init = TRUE;
	return (&(*this));
}

t_cmd	*builtins_parent(void)
{
	static t_cmd	this[] = {
	{"cd", ft_cd},
	{"unset", ft_unset},
	{"export", ft_export},
	{"exit", ft_exit},
	{NULL, NULL}
	};
	static int		is_init;

	if (is_init)
		return (&(*this));
	is_init = TRUE;
	return (&(*this));
}
