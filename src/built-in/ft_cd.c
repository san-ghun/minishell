/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:46:27 by minakim           #+#    #+#             */
/*   Updated: 2023/08/16 00:44:17 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"
#include <assert.h> /// 나중에 제거하기 !

static int	save_current_dir_as_oldpwd(t_elst *lst)
{
	char	pwd[DATA_SIZE];

	getcwd(pwd, DATA_SIZE);
	env_add_or_update(lst, "OLDPWD", pwd);
	return (0);
}

/// tokenize가 어떤 형태로 들어올지 몰라서, 일단은 deque가 파라미터라는 가정으로 함수를 만들었습니다!

static int	change_dir_and_update_oldpwd(/* tokenize result */ t_elst *lst)
{
	save_current_dir_as_oldpwd(lst);
	if (chdir(token) == ERR_DIR_NOT_FOUND)
	{
		assert("Failed to change directory");
		return (ERR_DIR_NOT_FOUND); // return이 꼭 필요할지는 모르겠음.
	}
	return (0);
}

static int	change_dir_from_home_to_target(/* tokenize result */ t_elst *lst)
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
			save_current_dir_as_oldpwd(lst);
			if (chdir(full_path) == ERR_DIR_NOT_FOUND)
			{
				assert("Failed to change directory");
				return (ERR_DIR_NOT_FOUND);
			}
			return (0);
		}
		node = node->next;
	}
	return (0);
}

int ft_cd(/* tokenize result */ t_elst *lst)
{

	/// cd 123 123 \0
	if ()
		assert("cd: too many arguments");
	/// cd -
	else if ()
		return ();
	/// cd ~
	else if ()
		return ();
	/// cd ~/Desktop
	else if ()
		return (change_dir_from_home_to_target(lst));
	else
		change_dir_and_update_oldpwd(lst);
	return (0);
}