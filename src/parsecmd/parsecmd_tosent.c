/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd_tosent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:57:49 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/22 21:17:28 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input(t_sent *node, char *margv[], int tmp)
{
	int	cnt;

	cnt = 0;
	if (!margv[tmp + 1])
	{
		node->output_flag = STDERR_FILENO;
		node->output_argv = \
			ft_strdup("syntax error: invalid token after redirection\n");
		return (-1);
	}
	cnt++;
	if (ft_strequ(margv[tmp], "<"))
		node->input_flag = REDI_RD_FLAG;
	else if (ft_strequ(margv[tmp], "<<"))
		node->input_flag = HDOC_FLAG;
	node->input_argv = ft_strdup(margv[tmp + 1]);
	return (cnt);
}

static int	handle_output(t_sent *node, char *margv[], int tmp)
{
	int	cnt;

	cnt = 0;
	if (!margv[tmp + 1])
	{
		node->output_flag = STDERR_FILENO;
		node->output_argv = \
			ft_strdup("syntax error: invalid token after redirection\n");
		return (-1);
	}
	cnt++;
	if (ft_strequ(margv[tmp], ">"))
		node->output_flag = REDI_WR_TRUNC_FLAG;
	else if (ft_strequ(margv[tmp], ">>"))
		node->output_flag = REDI_WR_APPEND_FLAG;
	node->output_argv = ft_strdup(margv[tmp + 1]);
	return (cnt);
}

typedef struct s_flag
{
	char	*flag_name;
	int		(*flag_func)(t_sent *node, char *margv[], int tmp);
}				t_flag;

static int	parse_redi(t_sent *node, char *margv[], int iter)
{
	int				i;
	int				cnt;
	static t_flag	flag_table[] = {
	{"<", handle_input},
	{"<<", handle_input},
	{">", handle_output},
	{">>", handle_output},
	{NULL, NULL}
	};

	i = -1;
	cnt = 0;
	while (flag_table[++i].flag_name)
		if (ft_strequ(margv[iter], flag_table[i].flag_name))
			cnt += flag_table[i].flag_func(node, margv, iter);
	return (cnt);
}

int	split_cmd(t_sent *node, char *margv[], int select, int i)
{
	int				len;
	int				tmp;
	int				iter;
	char			*tmparr[DATA_SIZE];

	len = -1;
	iter = select - 1;
	while (++iter < i)
	{
		tmp = 0;
		tmp += parse_redi(node, margv, iter);
		if (tmp > 0)
		{
			iter += tmp;
			continue ;
		}
		tmparr[++len] = margv[iter];
	}
	node->tokens_len = ++len;
	node->tokens = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	tmp = -1;
	while (++tmp < len)
		node->tokens[tmp] = ft_strdup(tmparr[tmp]);
	node->tokens[tmp] = NULL;
	return (i);
}
