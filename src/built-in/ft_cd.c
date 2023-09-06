/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:46:27 by minakim           #+#    #+#             */
/*   Updated: 2023/09/05 22:36:45 by minakim          ###   ########.fr       */
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
		perror("getcwd");
		return (CD_FAILURE);
	}
	getcwd(pwd, DATA_SIZE);
	env_add_or_update(lst, key, pwd);
	return (CD_SUCCESS);
}

static void update_pwd(t_elst *lst)
{
	char	pwd[DATA_SIZE];

	ft_bzero(pwd, DATA_SIZE);
	getcwd(pwd, DATA_SIZE);
	env_add_or_update(lst, "PWD", pwd);
}

static int change_dir_home(t_elst *lst)
{
	char	*home_path;

	home_path = env_getvalue(lst, "HOME");
	if (!home_path || chdir(home_path) == ERR_DIR_NOT_FOUND)
	{
		ft_printf("cd: HOME not set or directory not found\n");
		return (CD_FAILURE);
	}
	return (CD_SUCCESS);
}

static int change_dir_oldpwd(t_elst *lst)
{
	char	*oldpwd;

	oldpwd = env_getvalue(lst, "OLDPWD");
	if (!oldpwd || chdir(oldpwd) == ERR_DIR_NOT_FOUND)
	{
		ft_printf("cd: OLDPWD not set or directory not found\n");
		return (CD_FAILURE);
	}
	return (CD_SUCCESS);
}

static int change_dir_tilde(char *token, t_elst *lst)
{
	char	*home_path;
	char	full_path[DATA_SIZE];

	ft_bzero(full_path, DATA_SIZE);
	home_path = env_getvalue(lst, "HOME");
	if (home_path)
	{
		ft_strlcpy(full_path, home_path, sizeof(full_path));
		ft_strlcat(full_path, token + 1, sizeof(full_path));

		if (chdir(full_path) == ERR_DIR_NOT_FOUND)
		{
			ft_printf("cd: directory not found: %s\n", full_path);
			return (CD_FAILURE);
		}
	}
	else
	{
		ft_printf("cd: HOME not set\n");
		return (CD_FAILURE);
	}
	return (CD_SUCCESS);
}

int ft_cd(char **token, int size, t_elst *lst)
{
	save_current_dir_as_key(lst, "OLDPWD");
	if (size == 1 && ft_strequ(token[0], "cd"))
		return (change_dir_home(lst));
	if (size > 3)
	{
		ft_printf("cd: too many arguments\n");
		return (CD_FAILURE);
	}
	if (ft_strequ(token[1], "-"))
		return (change_dir_oldpwd(lst));
	if (token[1][0] == '~')
		return (change_dir_tilde(token[1], lst));
	if (chdir(token[1]) == ERR_DIR_NOT_FOUND)
	{
		ft_printf("cd: directory not found: %s\n", token[1]);
		return (CD_FAILURE);
	}
	update_pwd(lst);
	lst->g_exit = 0;
	return (CD_SUCCESS);
}
