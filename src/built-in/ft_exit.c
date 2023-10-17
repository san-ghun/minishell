/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:50:24 by minakim           #+#    #+#             */
/*   Updated: 2023/10/17 02:25:38 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_atoi_exit(const char *s)
{
	int	symbol;
	int	num;
	int	i;

	i = 0;
	num = 0;
	symbol = 1;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-')
		symbol = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]))
			num = (num * 10) + (s[i] - '0');
		else
			return (2);
		i++;
	}
	return (symbol * num);
}

void	ft_exit(t_sent *node, t_elst *lst)
{
//	printf("here is exit %d\n", getpid());
//	if (node->tokens_len == 1)
//		ft_putstr_fd("exit\n", STDOUT_FILENO);
//	if (node->tokens_len == 2)
//	{
//		lst->g_exit = ft_atoi_exit(node->tokens[1]);
//		ft_putstr_fd("exit\n", STDOUT_FILENO);
//	}
//	else if (node->tokens_len > 2)
//	{
//		ms_error("error\n");
//		lst->g_exit = 1;
//	}

	printf("Inside ft_exit, tokens_len: %d, pid: %d\n", node->tokens_len, getpid());  // 로그 추가

	if (node->tokens_len == 1) {
		printf("tokens_len is 1, exiting\n");  // 로그 추가
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	} else if (node->tokens_len == 2) {
		printf("tokens_len is 2, exiting with value %s\n", node->tokens[1]);  // 로그 추가
		lst->g_exit = ft_atoi_exit(node->tokens[1]);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	} else if (node->tokens_len > 2) {
		printf("tokens_len is greater than 2, error\n");  // 로그 추가
		ms_error("error\n");
		lst->g_exit = 1;
	}
}
