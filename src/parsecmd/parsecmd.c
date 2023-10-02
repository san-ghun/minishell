/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:38:54 by sanghupa          #+#    #+#             */
/*   Updated: 2023/10/02 15:18:49 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_punit(char *margv[], int select, int i)
{
	char	punit[DATA_SIZE];

	ft_strlcpy(punit, "", 2);
	while (select < i)
	{
		ft_strlcat(punit, margv[select], \
					ft_strlen(punit) + ft_strlen(margv[select]) + 1);
		select++;
		if (select < i)
			ft_strlcat(punit, " ", ft_strlen(punit) + 1 + 1);
	}
	return (ft_strdup(punit));
}

static int	cmdtosent(int margc, char *margv[], t_deque *deque)
{
	int		i;
	int		select;
	t_sent	*node;

	i = -1;
	select = 0;
	while (++i < margc)
	{
		if (ft_strequ(margv[i], "|"))
		{
			node = sent_new(get_punit(margv, select, i), \
							STDIN_FILENO, PIPE_FLAG);
			select = split_cmd(node, margv, select, i) + 1;
			deque_push_front(deque, node);
			i++;
		}
		if (margc == i + 1)
		{
			node = sent_new(get_punit(margv, select, i + 1), \
							STDIN_FILENO, STDOUT_FILENO);
			select = split_cmd(node, margv, select, i + 1);
			deque_push_front(deque, node);
		}
	}
	return (i);
}

void	exitstatus_marker(t_deque *deque)
{
	t_elst	*lst;
	t_sent	*node;
	int		i;

	lst = ms_env();
	node = deque->end;
	while (node != NULL)
	{
		i = 0;
		while (i < node->tokens_len)
		{
			if (ft_strequ(node->tokens[i], "$?"))
			{
				free(node->tokens[i]);
				node->tokens[i] = ft_itoa(lst->g_exit);
			}
			i++;
		}
		node = node->next;
	}
}

int	parsecmd(char *cmd, t_deque *deque, int debug_mode)
{
	int		i;
	int		margc;
	char	**margv;

	if (check_quotes(cmd, -1, 0))
	{
		ft_putstr_fd("error: Invalid quotation\n", 2);
		return (-1);
	}
	expand_cmd(cmd);
	margc = get_margc(cmd);
	margv = get_margv(cmd, margc);
	cmdtosent(margc, margv, deque);
	exitstatus_marker(deque);
	if (debug_mode)
	{
		i = 0;
		while (margv[i] != NULL)
			ft_printf("[%s] ", margv[i++]);
		ft_printf("\n");
	}
	i = 0;
	while (margv[i] != NULL)
		free(margv[i++]);
	free(margv);
	return (0);
}
