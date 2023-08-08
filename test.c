/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:15:06 by minakim           #+#    #+#             */
/*   Updated: 2023/08/08 15:21:49 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"



void tmp_print_all(t_dlst_data *lst)
{
	t_dlst *node;
	int i = -1;

	node = lst->begin;
	printf("------- start --------\n");
	while (node != NULL)
	{
		printf("%s\n", node->cnt);
		node = node->next;
	}
	printf("------- done --------\n");
}

int	main(int ac, char **av, char **envp)
{
	int i = -1;
	t_dlst_data *lst;
	t_dlst *node;

	lst = ft_memalloc(sizeof (t_dlst_data));
	while (envp[++i])
	{
		node = dlst_newnode(envp[i]);
		dlst_addrear(&lst, &node);
	}
	tmp_print_all(lst);
	dlst_dellst(lst);
}