/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:55 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/07 10:27:37 by sanghupa         ###   ########.fr       */
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
	int		j;
	t_sent	*node;

	i = 0;
	node = *sent;
	ft_printf("call sent_print(): printing sentence(s), head to tail.\n");
	if (!node)
		ft_printf("sentence is empty\n");
	while ((i++ <= MAX_ITER) && (node != NULL))
	{
		j = -1;
		ft_printf("p_unit: [%s]\n", node->p_unit);
		while (++j < node->tokens_len)
			ft_printf("[%d: %s] ", j, node->tokens[j]);
		ft_printf("\n");
		node = node->next;
	}
	return ;
}
