/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:03:00 by sanghupa          #+#    #+#             */
/*   Updated: 2023/11/02 10:55:26 by sanghupa         ###   ########.fr       */
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

static int	append_izero(char *str, char *cmd, t_elst *lst)
{
	char	*str_gexit;
	int		ret;

	ret = 0;
	if (cmd[1] == '\0' || cmd[1] == '\"')
	{
		ft_strlcat(str, "$", ft_strlen(str) + 2);
		ret = 0;
	}
	else if (cmd[1] == '?')
	{
		str_gexit = ft_itoa(lst->g_exit);
		ft_strlcat(str, str_gexit, ft_strlen(str) + ft_strlen(str_gexit) + 1);
		ret = 1;
		free(str_gexit);
	}
	return (ret);
}

int	append_env(char *str, char *cmd)
{
	int		i;
	t_elst	*lst;
	t_env	*node;

	i = 1;
	while (ft_isalnum(cmd[i]))
		i++;
	i--;
	lst = ms_env();
	if (i == 0)
		return (append_izero(str, cmd, lst));
	node = lst->begin;
	while (node != NULL)
	{
		if (ft_strnequ(node->key, &cmd[1], i))
		{
			ft_strlcat(str, node->value, \
						ft_strlen(str) + ft_strlen(node->value) + 1);
			break ;
		}
		node = node->next;
	}
	if (cmd[0] == '~')
		i = 0;
	return (i);
}

void	expand_cmd(char *cmd)
{
	char	str[MAX_COMMAND_LEN];
	int		i;
	uint8_t	quote_s;
	uint8_t	quote_d;

	ft_bzero(&str[0], MAX_COMMAND_LEN);
	i = -1;
	quote_s = 0;
	quote_d = 0;
	while (cmd[++i] != '\0')
	{
		if (cmd[i] == '\'' && quote_d != 1)
			quote_s ^= 1;
		else if (cmd[i] == '\"' && quote_s != 1)
			quote_d ^= 1;
		if (cmd[i] == '$' && quote_s != 1)
			i += append_env(&str[0], &cmd[i]);
		else if (cmd[i] == '~' && quote_s != 1)
			i += append_env(&str[0], "~HOME");
		else
			ft_strlcat(&str[0], &cmd[i], ft_strlen(str) + 2);
	}
	ft_bzero(cmd, MAX_COMMAND_LEN);
	ft_strlcpy(cmd, str, ft_strlen(str) + 1);
	return ;
}

int	ms_strndup_helper(const char *src, char *new, int len)
{
	int		i;
	int		j;
	uint8_t	quote_s;
	uint8_t	quote_d;

	i = -1;
	j = -1;
	quote_s = 0;
	quote_d = 0;
	while (src[++i] != '\0' && i < len)
	{
		if (src[i] == '\'' && quote_d != 1)
			quote_s ^= 1;
		else if (src[i] == '\"' && quote_s != 1)
			quote_d ^= 1;
		if (!quote_d)
			if (src[i] == '\'')
				continue ;
		if (!quote_s)
			if (src[i] == '\"')
				continue ;
		new[++j] = src[i];
	}
	return (i);
}
