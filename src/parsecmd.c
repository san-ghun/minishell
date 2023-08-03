/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:38:54 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/03 13:15:52 by sanghupa         ###   ########.fr       */
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
			if (cmd[i] == '\"')
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

void	tokenize_cmdtoprocess(char *cmd, char *tokens[])
{
	int		i;
	char	*token;

	i = 0;
	token = ft_strtok(cmd, ";|");
	while ((token != NULL) && (i < MAX_TOKENS))
	{
		token = ft_strtrim(token, " ");
		tokens[i++] = token;
		token = ft_strtok(NULL, ";|");
	}
	tokens[i] = NULL;
	return ;
}

t_sent	*p_to_sent(char *p_unit)
{
	int		i;
	char	tmp[MAX_TOKENS];
	char	*token;
	char	*tokens[MAX_TOKENS];

	i = 0;
	ft_strlcpy(tmp, "", 2);
	ft_strlcpy(tmp, p_unit, ft_strlen(p_unit) + 1);

	// TODO:
	// tokenize process unit into pieces and 
	// store tokens in t_sent
	token = ft_strtok(p_unit, " ");
	while ((token != NULL) && (i < MAX_TOKENS))
	{
		token = ft_strtrim(token, " ");
		tokens[i++] = token;
		token = ft_strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return (sent_new(tmp, tokens, 0, 0));
}

int	parsecmd(char *cmd, t_deque *deque)
{
	int		i;
	char	*p_units[MAX_TOKENS];

	// check single quote and double quote 
	// whether they are properly closed
	if (check_quotes(cmd, -1, 0))
	{
		// quote_error();
		ft_putstr_fd("error: Invalid quotation\n", 2);
		exit(EXIT_SUCCESS);
	}

	// tokenize into process unit, based on `;`, `|`, and `\0`
	// tokenize cmd and properly handle quotes
	tokenize_cmdtoprocess(cmd, p_units);

	// store process units in t_sent
	// push t_sent into t_deque
	i = 0;
	while (p_units[i] != NULL)
		deque_push_front(deque, p_to_sent(p_units[i++]));
	i = 0;
	while (p_units[i] != NULL)
		free(p_units[i++]);
	return (0);
}
