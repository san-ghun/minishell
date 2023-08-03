/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:55 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/03 12:10:50 by sanghupa         ###   ########.fr       */
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
	t_sent	*node;
	char	*tmp;

	i = 0;
	node = *sent;
	ft_printf("call sent_print(): printing sentence(s), head to tail.\n");
	if (!node)
		ft_printf("sentence is empty\n");
	while ((i++ <= MAX_ITER) && (node != NULL))
	{
		// tmp = *node->tokens;
		// ft_printf("%d: ", i);
		// while (tmp != NULL)
		// 	ft_printf("[%s] ", tmp++);
		// ft_printf("\n");
		ft_printf("[%s] ", node->p_unit);
		node = node->next;
	}
	ft_printf("\n");
	return ;
}
