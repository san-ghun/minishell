/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:15:06 by minakim           #+#    #+#             */
/*   Updated: 2023/08/07 10:16:21 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define FALSE	0
#define TRUE	1

typedef void		(*t_fun)(int, char **);

// int	main(int argc, char *argv[])
// {
// 	char	cmd[MAX_COMMAND_LEN];
// 	t_deque	*deque;

// 	deque = deque_init();
// 	readcmd(cmd);
// 	parsecmd(cmd, deque);

// 	ft_printf("\n");
// 	sent_print(&deque->end);
// 	ft_printf("\n");
// 	deque_print_all(deque);

// 	sent_delall(&deque->end);
// 	deque_del(deque);
// }

int	main(int argc, char *argv[])
{
	int i = 0;
	char *a;
	char p[2] = "";
	char *t;
	ft_strlcpy(a, "echo \"123\"", 11);
	p[0] = *(a + ft_strspn(a, " ") - 1);
	t = ft_strtok(a, p);
	ft_printf("[%s]\n", t);
	a += ft_strspn(a, "\'\" ");
	p[0] = *(a + ft_strspn(a, "\'\" ") - 1);
	while (t != NULL)
	{
		ft_printf("[%s]\n", t);
		a += ft_strspn(a, "\'\" ");
		p[0] = *(a + ft_strspn(a, "\'\" ") - 1);
		t = ft_strtok(NULL, p);
	}
	return (0);
}
