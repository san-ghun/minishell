/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:15:06 by minakim           #+#    #+#             */
/*   Updated: 2023/08/14 23:09:11 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"
#include <assert.h>

void ft_print_env(t_env *node)
{
	printf("%s=%s\n", node->key, node->value);
}

void tmp_print_all(t_elst *lst)
{
	t_env *node;
	int i = -1;

	node = lst->begin;
	printf("------- start --------\n");
	while (node != NULL)
	{
		ft_print_env(node);
		node = node->next;
	}
	printf("------- done --------\n");
}

int	main(int ac, char **av, char **envp)
{
	int i = -1;
	t_elst *lst;
	t_env *node;

	lst = env_to_dll(envp);
	tmp_print_all(lst);
	env_dellst(lst);
}