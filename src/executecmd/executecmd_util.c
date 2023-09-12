/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 23:54:28 by minakim           #+#    #+#             */
/*   Updated: 2023/09/13 00:01:12 by minakim          ###   ########.fr       */
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