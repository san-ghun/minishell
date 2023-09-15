/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 23:54:28 by minakim           #+#    #+#             */
/*   Updated: 2023/09/13 15:47:53 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_2d(char **targets)
{
	int	i;

	i = -1;
	while (targets[++i])
		free(targets[i]);
	free(targets);
	targets = NULL;
}

int	exe_error(int target, char *error_msg)
{
	if (target == -1)
	{
		ft_putendl_fd(error_msg, 1);
		return (1);
	}
	return (0);
}

char	*setfilename(char **tokens, char *delim)
{
	int	i = 0;

	while (tokens[i])
	{
		if (ft_strnstr(tokens[i], delim, ft_strlen(tokens[i])))
			return tokens[i + 1];
		i++;
	}
	return (NULL);
}

void	remove_redi_tokens(t_sent *node, char *delim)
{
	char **new_tokens;
	int i;
	int j;
	int symbol;

	i = 0;
	j = 0;
	symbol = 0;
	new_tokens = (char **) malloc(sizeof(char *) * (node->tokens_len));
	while (node->tokens[i]) {
		if (!ft_strequ(node->tokens[i], delim))
			new_tokens[j++] = node->tokens[i];
		else if (!symbol) {
			symbol = 1;
			free(node->tokens[i]);
			i++;
		}
		i++;
	}
	new_tokens[j] = NULL;
	free(node->tokens);
	node->tokens = new_tokens;
	node->tokens_len -= 1;
}