/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:50:24 by minakim           #+#    #+#             */
/*   Updated: 2023/10/04 19:09:29 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_atoi_exit(const char *s)
{
	int	symbol;
	int	num;

	num = 0;
	symbol = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '-')
		symbol = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (ft_isdigit(*s))
			num *= 10 + (*s - '0');
		else
			return (2);
		s++;
	}
	return (symbol * num);
}

void	ft_exit(t_sent *node, t_elst *lst)
{
	if (node->tokens_len == 2)
	{
		lst->g_exit = ft_atoi_exit(node->tokens[1]);
		ft_printf("exit\n");
	}
	else if (node->tokens_len > 2)
	{
		ms_error("error\n");
		lst->g_exit = 1;
	}
}