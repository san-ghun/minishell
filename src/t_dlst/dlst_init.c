/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:11:49 by minakim           #+#    #+#             */
/*   Updated: 2023/08/08 13:28:13 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

void	dlst_updatesize(t_dlst_data *lst, int add)
{
	if ((lst)->size < 0)
		(lst)->size = -1;
	(lst)->size += add;
}

t_dlst	*dlst_newnode(char *str)
{
	t_dlst	*new;

	if (!str)
		return (NULL);
	new = ft_memalloc(sizeof(t_dlst));
	if (!new)
		return (NULL);
	new->cnt = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
