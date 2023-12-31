/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:10:51 by minakim           #+#    #+#             */
/*   Updated: 2023/11/17 16:19:23 by minakim          ###   ########.fr       */
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

void	ft_ms_exit(t_sent *cmd, t_deque *deque, int exit_code)
{
	if (cmd && !(cmd->next))
	{
		sent_delall(&cmd);
		deque_del(deque);
		env_dellst(ms_env());
	}
	exit(exit_code);
}

char	*ms_find_path(char *cmd)
{
	int		i;
	char	**paths;
	char	*ppath;
	char	*path;

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	if (check_dir(cmd, &path) > 0 || !ft_getenv(ms_env(), "PATH"))
		return (path);
	paths = ft_split(ft_getenv(ms_env(), "PATH"), ':');
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

t_ctx	*ms_ctx(void)
{
	static t_ctx	this;
	static int		is_init;

	if (is_init)
		return (&this);
	this = (t_ctx){
		.i = 0,
		.cmd_count = 0,
		.wait_count = 0,
		.input_fd = STDIN_FILENO,
		.output_fd = STDOUT_FILENO
	};
	is_init = TRUE;
	return (&this);
}
