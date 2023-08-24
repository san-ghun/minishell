/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:38:54 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/24 17:10:19 by sanghupa         ###   ########.fr       */
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

void	tokenize_cmdtoprocess(char *cmd, char *tokens[], char *charset)
{
	int		i;
	char	*token;

	i = 0;
	token = ft_strtok(cmd, charset);
	while ((token != NULL) && (i < MAX_TOKENS))
	{
		token = ft_strtrim(token, " ");
		tokens[i++] = token;
		token = ft_strtok(NULL, charset);
	}
	tokens[i] = NULL;
	return ;
}

t_sent	*p_to_sent(char *p_unit, int is_redir, int is_pipe)
{
	char	cmd[MAX_COMMAND_LEN];

	ft_strlcpy(cmd, "", 2);
	ft_strlcpy(cmd, p_unit, ft_strlen(p_unit) + 1);
	return (sent_new(cmd, is_redir, is_pipe));
}

int	parsecmd(char *cmd, t_deque *deque)
{
	int		i;
	int		j;
	char	*p_units[MAX_TOKENS];
	char	*p_units_tmp[MAX_TOKENS];
	t_sent	*node;

	if (check_quotes(cmd, -1, 0))
	{
		ft_putstr_fd("error: Invalid quotation\n", 2);
		return (-1);
	}

	// tokenize into process unit, based on `;` and `\0`
	// tokenize cmd and properly handle quotes
	tokenize_cmdtoprocess(cmd, p_units, ";");

	// store process units in t_sent
	// push t_sent into t_deque
	i = 0;
	while (p_units[i] != NULL)
	{
		if (ft_strchr(p_units[i], '|'))
		{
			j = 0;
			tokenize_cmdtoprocess(p_units[i], p_units_tmp, "|");
			while (p_units_tmp[j] != NULL)
			{
				node = sent_new(p_units_tmp[j++], 0, 1);
				deque_push_front(deque, node);
			}
			j = 0;
			while (p_units_tmp[j] != NULL)
				free(p_units_tmp[j++]);
			i++;
			continue ;
		}
		node = sent_new(p_units[i++], 0, 0);
		deque_push_front(deque, node);
	}
	i = 0;
	while (p_units[i] != NULL)
		free(p_units[i++]);
	return (0);
}
