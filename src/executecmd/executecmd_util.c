/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:10:51 by minakim           #+#    #+#             */
/*   Updated: 2023/10/20 13:36:18 by minakim          ###   ########.fr       */
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

int	ft_free_check(char *path, char *menvp[], int ret)
{
	ft_free_2d(menvp);
	free(path);
	return (ret);
}

char	*ms_find_path(char *cmd)
{
	int		i;
	char	**paths;
	char	*ppath;
	char	*path;

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	if (!ft_getenv(ms_env(), "PATH"))
		return (0);
	paths = ft_split(ft_getenv(ms_env(), "PATH") + 5, ':');
	i = -1;
	while (paths[++i] != NULL)
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
	}
	ft_free_2d(paths);
	return (0);
}

