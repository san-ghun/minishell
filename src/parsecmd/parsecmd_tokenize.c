/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd_tokenize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:43:14 by sanghupa          #+#    #+#             */
/*   Updated: 2023/10/14 15:06:18 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_margc(char *cmd);
char	**get_margv(char *cmd, int margc);

int	get_margc(char *cmd)
{
	int		i;
	int		cnt;
	uint8_t	quote_s;
	uint8_t	quote_d;

	i = -1;
	cnt = 0;
	quote_s = 0;
	quote_d = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && quote_d != 1)
			quote_s ^= 1;
		else if (cmd[i] == '\"' && quote_s != 1)
			quote_d ^= 1;
		if (!ft_isspace(cmd[i]) && (ft_isspace(cmd[i + 1]) || !(cmd[i + 1])))
			if (!quote_s && !quote_d)
				cnt++;
	}
	return (cnt);
}

static int	skip_spaces(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!ft_isspace(s[i]))
			break ;
	return (i);
}

static int	get_nexti(char *s)
{
	int		i;
	uint8_t	quote_s;
	uint8_t	quote_d;

	i = -1;
	quote_s = 0;
	quote_d = 0;
	while (s[++i])
	{
		if (s[i] == '\'' && quote_d != 1)
			quote_s ^= 1;
		else if (s[i] == '\"' && quote_s != 1)
			quote_d ^= 1;
		if (!quote_s && !quote_d && ft_isspace(s[i]))
			break ;
	}
	return (i);
}

char	*ms_strndup(const char *src, int len)
{
	int		i;
	int		j;
	char	*new;

	new = (char *)ft_memalloc(len + 1);
	if (!new)
		return (NULL);
	i = -1;
	j = -1;
	while (src[++i] != '\0' && i < len)
	{
		if ((src[i] == '\"') || (src[i] == '\''))
			continue ;
		new[++j] = src[i];
	}
	while (i < len)
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}

char	**get_margv(char *cmd, int margc)
{
	int		i;
	int		select;
	int		nexti;
	char	**margv;

	margv = (char **)ft_memalloc(sizeof(char *) * (margc + 1));
	i = -1;
	select = 0;
	while (++i < margc)
	{
		select += skip_spaces(&cmd[select]);
		nexti = get_nexti(&cmd[select]);
		margv[i] = ms_strndup(&cmd[select], nexti);
		select += nexti;
	}
	return (margv);
}
