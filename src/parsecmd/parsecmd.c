/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:38:54 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/04 12:54:57 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *cmd, int index, int status)
{
	int	i;

	i = index;
	while (cmd[++i] != '\0')
	{
		if (status == 0)
		{
			if (cmd[i] == '\'')
				i = check_quotes(cmd, i, '\'');
			else if (cmd[i] == '\"')
				i = check_quotes(cmd, i, '\"');
			if (i == -1)
				return (1);
			continue ;
		}
		if ((status == '\'') && (cmd[i] == '\''))
			return (i);
		if ((status == '\"') && (cmd[i] == '\"'))
			return (i);
		if (cmd[i + 1] == '\0')
			return (-1);
	}
	if ((status == '\'') || (status == '\"'))
		return (-1);
	return (0);
}

static char	*get_punit(char *margv[], int i, int select)
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

static int	split_cmd(t_sent *node, char *margv[], int i, int select)
{
	int	tmp;

	tmp = 0;
	node->tokens_len = i - select;
	node->tokens = (char **)ft_memalloc(sizeof(char *) * (i - select) + 1);
	while (select < i)
		node->tokens[tmp++] = ft_strdup(margv[select++]);
	return (select);
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
			node = sent_new(get_punit(margv, i, select), 0, 1);
			select = split_cmd(node, margv, i, select) + 1;
			deque_push_front(deque, node);
			i++;
		}
		else if (margc == i + 1)
		{
			node = sent_new(get_punit(margv, i + 1, select), 0, 0);
			select = split_cmd(node, margv, i + 1, select);
			deque_push_front(deque, node);
		}
	}
	return (i);
}

int	parsecmd(char *cmd, t_deque *deque, t_elst *elst)
{
	int		i;
	int		margc;
	char	**margv;

	if (check_quotes(cmd, -1, 0))
	{
		ft_putstr_fd("error: Invalid quotation\n", 2);
		return (-1);
	}
	expand_cmd(cmd, elst);
	margc = get_margc(cmd);
	margv = get_margv(cmd, margc);
	cmdtosent(margc, margv, deque);

	ft_printf("margc: %d\n", margc);
	i = 0;
	while (margv[i] != NULL)
	{
		ft_printf("[%s] ", margv[i]);
		free(margv[i++]);
	}
	free(margv);
	ft_printf("\n");
	return (0);
}
