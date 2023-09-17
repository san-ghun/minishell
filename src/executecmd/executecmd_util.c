/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:10:51 by minakim           #+#    #+#             */
/*   Updated: 2023/09/17 13:10:55 by minakim          ###   ########.fr       */
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

char	*ms_find_path(char *cmd, char *envp[])
{
	int		i;
	char	**paths;
	char	*ppath;
	char	*path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		ppath = ft_strjoin(paths[i], "/");
		path = ft_strjoin(ppath, cmd);
		free(ppath);
		if (access(path, F_OK) == 0)
		{
			ft_free_2d(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_2d(paths);
	return (0);
}