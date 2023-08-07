/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:36 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/03 01:43:30 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sent	*sent_getone(t_sent *sent[], char *cmd);
t_sent	*sent_getlast(t_sent *sent);
t_sent	*sent_getfront(t_sent *sent);

t_sent	*sent_getone(t_sent *sent[], char *cmd)
{
	int		i;
	t_sent	*node;
	char	*tmp;

	if (!sent || !(*sent))
		return (NULL);
	i = 0;
	node = *sent;
	while ((i++ <= MAX_ITER) && (node != NULL))
	{
		tmp = *node->tokens;
		while (tmp != NULL)
		{
			if (ft_strncmp(tmp, cmd, ft_strlen(cmd)) == 0)
				return (node);
			tmp++;
		}
		node = node->next;
	}
	return (NULL);
}

t_sent	*sent_getlast(t_sent *sent)
{
	if (!sent)
		return (NULL);
	while (sent->next != NULL)
		sent = sent->next;
	return (sent);
}

t_sent	*sent_getfront(t_sent *sent)
{
	if (!sent)
		return (NULL);
	while (sent->prev != NULL)
		sent = sent->prev;
	return (sent);
}
