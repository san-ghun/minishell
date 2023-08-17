/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:46:27 by minakim           #+#    #+#             */
/*   Updated: 2023/08/17 20:59:24 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

static int	save_current_dir_as_key(t_elst *lst, char *key)
{
	char	pwd[DATA_SIZE];

	getcwd(pwd, DATA_SIZE);
	env_add_or_update(lst, key, pwd);
	return (0);
}

static int	change_dir_and_update_oldpwd(char *token /* tokenize result */, t_elst *lst)
{
	save_current_dir_as_key(lst, "OLDPWD");
	if (chdir(token) == ERR_DIR_NOT_FOUND)
	{
		perror("cd");
		return (ERR_DIR_NOT_FOUND); // return이 꼭 필요할지는 모르겠음.
	}
	return (0);
}

static int	change_dir_from_home_to_target(char *token /* tokenize result */, t_elst *lst)
{
	char	*path;
	char 	*home_path;
	char    full_path[DATA_SIZE];
	t_env	*node;

	node = lst->begin;
	while (node)
	{
		if (ft_strequ(node->key, "HOME"))
		{
			home_path = node->value;
			path = ft_strpbrk(token, "~") + 1;
			ft_strlcpy(full_path, home_path, sizeof(full_path));
			ft_strlcat(full_path, path, sizeof(full_path));
			save_current_dir_as_key(lst, "OLDPWD");
			if (chdir(full_path) == ERR_DIR_NOT_FOUND)
			{
				perror("cd");
				return (ERR_DIR_NOT_FOUND);
			}
			return (0);
		}
		node = node->next;
	}
	return (0);
}

static int	change_dir_to_home(t_elst *lst)
{
	char	*path;
	char 	*home_path;
	t_env	*node;

	node = lst->begin;
	while (node)
	{
		if (ft_strequ(node->key, "HOME"))
		{
			home_path = node->value;
			save_current_dir_as_key(lst, "OLDPWD");
			if (chdir(home_path) == ERR_DIR_NOT_FOUND)
			{
				perror("cd");
				return (ERR_DIR_NOT_FOUND);
			}
			return (0);
		}
		node = node->next;
	}
	return (0);
}

static int	change_dir_to_past_path(t_elst *lst)
{
	t_env	*node;
	char	*path;

	path = NULL;
	node = lst->begin;
	while (node)
	{
		if (ft_strequ(node->key, "OLDPWD"))
		{
			path = node->value;
			break ;
		}
		node = node->next;
	}
	if (path == NULL)
	{
		fprintf(stderr, "cd: OLDPWD not set\n");
		return (1);
	}
	if (chdir(path) == ERR_DIR_NOT_FOUND)
	{
		perror("cd");
		return (ERR_DIR_NOT_FOUND);
	}
	save_current_dir_as_key(lst, "OLDPWD");
	return (0);
}

int ft_cd(char **token, int size/* tokenize result */, t_elst *lst)
{

	/// cd
	if (size == 1 && ft_strequ(token[0], "cd"))
		return (change_dir_to_home(lst));
	/// cd 123 123 \0
	if (size != 2)
		ft_printf("cd: too many arguments\n");
	/// cd -
	else if (ft_strequ(token[1], "-"))
		return (change_dir_to_past_path(lst));
	/// cd ~
	else if (ft_strequ(token[1], "~"))
		return (change_dir_to_home(lst));
	/// cd ~/Desktop
	else if (ft_strequ(token[1], "~/"))
		return (change_dir_from_home_to_target(token[1], lst));
	else
		change_dir_and_update_oldpwd(token[1], lst);
	return (0);
}