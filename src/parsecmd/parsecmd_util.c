/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:03:00 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/02 12:35:19 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_env(char *str, char *cmd, char *envp[])
{
	int		i;
	int		envpi;

	i = 1;
	while (ft_isalnum(cmd[i]))
		i++;
	i--;
	envpi = 0;
	while (envp[envpi])
	{
		if ((ft_strncmp(envp[envpi], &cmd[1], i) == 0) && \
			(envp[envpi][i] == '='))
		{
			ft_strlcat(str, &envp[envpi][i + 1], \
				ft_strlen(str) + ft_strlen(&envp[envpi][i + 1]) + 1);
			break ;
		}
		envpi++;
	}
	return (i);
}

static int	append_env_edit(char *str, char *cmd, t_elst *lst)
{
	int		i;
	t_env	*node;

	i = 1;
	while (ft_isalnum(cmd[i]))
		i++;
	i--;
	node = lst->begin;
	while (node != NULL)
	{
		if (ft_strnequ(node->key, &cmd[1], i))
		{
			ft_strlcat(str, node->value, ft_strlen(str) + ft_strlen(node->value) + 1);
			break ;
		}
		node = node->next;
	}
	return (i);
}

void	expand_dallar(char *cmd, char *envp[])
{
	char	str[MAX_COMMAND_LEN];
	int		i;
	uint8_t	quote_s;
	uint8_t	quote_d;

	ft_strlcpy(str, "", 2);
	i = 0;
	quote_s = 0;
	quote_d = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'' && quote_d != 1)
			quote_s ^= 1;
		else if (cmd[i] == '\"' && quote_s != 1)
			quote_d ^= 1;
		if (cmd[i] == '$' && quote_s != 1)
			i += append_env(&str[0], &cmd[i], envp);
		else
			ft_strlcat(&str[0], &cmd[i], ft_strlen(str) + 2);
		i++;
	}
	ft_strlcpy(cmd, str, ft_strlen(str) + 1);
	return ;
}

void	expand_tilde(char *cmd, char *envp[])
{
	char	str[MAX_COMMAND_LEN];
	int		i;
	uint8_t	quote_s;
	uint8_t	quote_d;

	ft_strlcpy(str, "", 2);
	i = 0;
	quote_s = 0;
	quote_d = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'' && quote_d != 1)
			quote_s ^= 1;
		else if (cmd[i] == '\"' && quote_s != 1)
			quote_d ^= 1;
		if (cmd[i] == '~' && quote_s != 1)
			i += append_env(&str[0], "~HOME", envp);
		else
			ft_strlcat(&str[0], &cmd[i], ft_strlen(str) + 2);
		i++;
	}
	ft_strlcpy(cmd, str, ft_strlen(str) + 1);
	return ;
}

void	expand_tilde_edit(char *cmd, t_elst *lst)
{
	char	str[MAX_COMMAND_LEN];
	int		i;
	uint8_t	quote_s;
	uint8_t	quote_d;

	ft_strlcpy(str, "", 2);
	i = 0;
	quote_s = 0;
	quote_d = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'' && quote_d != 1)
			quote_s ^= 1;
		else if (cmd[i] == '\"' && quote_s != 1)
			quote_d ^= 1;
		if (cmd[i] == '~' && quote_s != 1)
			i += append_env_edit(&str[0], "~HOME", lst);
		else
			ft_strlcat(&str[0], &cmd[i], ft_strlen(str) + 2);
		i++;
	}
	ft_strlcpy(cmd, str, ft_strlen(str) + 1);
	return ;
}
