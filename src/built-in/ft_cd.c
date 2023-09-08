/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:46:27 by minakim           #+#    #+#             */
/*   Updated: 2023/09/08 13:54:46 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

#define CD_SUCCESS 0
#define CD_FAILURE 1

// TODO: need to check what can be error code (i.g. g_exit)
static int	save_current_dir_as_key(t_elst *lst, char *key)
{
	char	pwd[DATA_SIZE];

	ft_bzero(pwd, DATA_SIZE);
	if (!getcwd(pwd, DATA_SIZE))
	{
		perror("getcwd"); // TODO: add overall error check
		return (CD_FAILURE);
	}
	getcwd(pwd, DATA_SIZE);
	env_add_or_update(lst, key, pwd);
	return (CD_SUCCESS);
}

static int change_dir_tilde(char *token, t_elst *lst)
{
	char	*home_path;
	char	full_path[DATA_SIZE];

	ft_bzero(full_path, DATA_SIZE);
	home_path = env_getvalue(lst, "HOME");
	save_current_dir_as_key(lst, "OLDPWD");
	if (!home_path)
	{
		ft_printf("cd: HOME not set\n");
		return (CD_FAILURE);
	}
	ft_strlcpy(full_path, home_path, sizeof(full_path));
	ft_strlcat(full_path, token + 1, sizeof(full_path));
	if (chdir(full_path) == ERR_DIR_NOT_FOUND)
	{
		ft_printf("cd: directory not found: %s\n", full_path);
		return (CD_FAILURE);
	}
	else
		lst->g_exit = 0;
	return (CD_SUCCESS);
}

static int	change_dir_key(t_elst *lst, char *key)
{
	char	*path;

	path = env_getvalue(lst, key);
	save_current_dir_as_key(lst, "OLDPWD");
	if (!path || chdir(path) == ERR_DIR_NOT_FOUND)
	{
		ft_printf("cd: directory not found: %s\n", path);
		return (CD_FAILURE);
	}
	else
		lst->g_exit = 0;
}

static int	change_dir(t_elst *lst)
{
	char	path[DATA_SIZE];

	getcwd(path, DATA_SIZE);
	save_current_dir_as_key(lst, "OLDPWD");
	if (chdir(path) == ERR_DIR_NOT_FOUND)
	{
		ft_printf("cd: directory not found: %s\n", path);
		return (CD_FAILURE);
	}
	else
		lst->g_exit = 0;
}

int ft_cd(t_sent *node, t_elst *lst)
{
	char	**tokens;
	int 	size;

	tokens = node->tokens;
	size = node->tokens_len;
	if (size == 1 && ft_strequ(tokens[0], "cd"))
		return (change_dir_key(lst, "HOME"));
	if (size > 3)
	{
		ft_printf("cd: too many arguments\n");
		return (CD_FAILURE);
	}
	if (tokens[1][0] == '-')
		return (change_dir_key(lst, "OLDPWD"));
	if (tokens[1][0] == '~')
		return (change_dir_tilde(tokens[1], lst));
	if (chdir(tokens[1]) == ERR_DIR_NOT_FOUND)
	{
		ft_printf("cd: directory not found: %s\n", tokens[1]);
		return (CD_FAILURE);
	}
	else
		return (change_dir(lst));
}