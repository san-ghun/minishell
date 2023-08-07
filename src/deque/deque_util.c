/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:39:17 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/07 10:18:32 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	deque_size(t_deque *deque);
int		deque_isempty(t_deque *deque);
t_sent	*deque_front(t_deque *deque);
t_sent	*deque_back(t_deque *deque);
void	deque_print_all(t_deque *deque);

size_t	deque_size(t_deque *deque)
{
	return (deque->size);
}

int	deque_isempty(t_deque *deque)
{
	if (deque_size(deque) == 0)
		return (1);
	return (0);
}

t_sent	*deque_front(t_deque *deque)
{
	return (deque->begin);
}

t_sent	*deque_back(t_deque *deque)
{
	return (deque->end);
}

void	deque_print_all(t_deque *deque)
{
	int		i;
	int		j;
	t_sent	*node;
	char	*tmp;

	i = 0;
	node = deque->begin;
	ft_printf("call deque_print_all(): printing deque, begin to end.\n");
	if (!node)
		ft_printf("deque is empty\n");
	while (node != NULL)
	{
		j = -1;
		ft_printf("p_unit: [%s]\n", node->p_unit);
		while (++j < node->tokens_len)
			ft_printf("%d:[%s] ", j, node->tokens[j]);
		ft_printf("\n");
		node = node->prev;
	}
}
