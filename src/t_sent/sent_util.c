/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:55 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/01 13:28:38 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	sent_len(t_sent *sent[]);
void	sent_print(t_sent *sent[]);

size_t	sent_len(t_sent *sent[])
{
	size_t	len;
	t_sent	*tmp;

	if (!sent || !(*sent))
		return (0);
	len = 1;
	tmp = *sent;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

void	sent_print(t_sent *sent[])
{
	int		i;
	t_sent	*tmp;

	i = 0;
	tmp = *sent;
	if (!tmp)
		ft_printf("sentence is empty\n");
	while ((i++ <= MAX_ITER) && (tmp != NULL))
	{
//		ft_printf("-%d:%s:%d- ", tmp->prefix, tmp->cmd, tmp->next);
		tmp = tmp->next;
	}
	ft_printf("\n");
	return ;
}
