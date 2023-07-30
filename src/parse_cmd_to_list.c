/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:59:33 by minakim           #+#    #+#             */
/*   Updated: 2023/07/30 14:02:18 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_semi(char *cmd)
{
	int		i;
	int		count;
	uint8_t	quotes;

	count = 1;
	quotes = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '"')
			quotes ^= 1;
		else if (cmd[i] == ';' && !quotes)
			count++;
	}
	return (count);
}

t_deque	*parse_cmd_to_list(char *cmd, t_deque *lst)
{
	t_sent	*new;
	int 	size;
	int 	i;
	int 	j;

	size = count_semi(cmd);
	i = -1;
	j = -1;
	while (++i < size)
	{
		j++;
		new = sent_new(ft_strcdup(&cmd[j], ';'), 0, 0);
		while(cmd[j] && cmd[j] != ';')
			j++;
		new = new->next;
	}
	lst->begin = sent_getfront(new);
	lst->end = sent_getlast(new);
	lst->size = size;
	return (lst);
}