/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:46:27 by minakim           #+#    #+#             */
/*   Updated: 2023/10/03 13:08:20 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CD_SUCCESS 0
#define CD_FAILURE 1

/// @brief The functions in this file are partially complete, but
///are incomplete. I'll update them as I go along.
int	ft_arrayjoin(char dest[DATA_SIZE], \
const char src1[DATA_SIZE], const char src2[DATA_SIZE])
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(src1);
	len2 = ft_strlen(src2);
	if (len1 + len2 + 1 > DATA_SIZE)
		return (0);
	ft_strlcpy(dest, src1, DATA_SIZE);
	ft_strlcat(dest, src2, DATA_SIZE);
	return (1);
}

void	ft_pathcpy(t_elst *lst, char *key, char path[], int size)
{
	char	*value;

	ft_bzero(path, size);
	value = ft_getenv(lst, key);
	if (value == NULL)
		return ;
	ft_strlcpy(path, value, size);
}

void	cd_tilde(char full_path[DATA_SIZE], char *token, t_elst *lst)
{
	char	home_path[DATA_SIZE];

	ft_bzero(full_path, DATA_SIZE);
	ft_pathcpy(lst, "HOME", home_path, DATA_SIZE);
	ft_arrayjoin(full_path, home_path, token + 1);
}

/// @return In bash shell, these errors commonly lead to a return code of 1.
/// ENOENT: The specified file or directory does not exist.
/// EACCES: Permission denied to access the specified directory.
/// ENOTDIR: A part of the specified path is not a directory.
/// ELOOP: Too many symbolic links were encountered in translating the pathname.
/// ENAMETOOLONG: The specified path name is too long.
/// ENOMEM: Insufficient kernel memory was available.
/// EFAULT: The specified path points outside your accessible address space.
/// ERANGE: The specified path is too long to fit into the provided buffer.
//int	cd_failure(void)
//{
//	if (errno == ENOENT || errno == EACCES || errno == ENOTDIR ||
//		errno == ELOOP || errno == ENAMETOOLONG || errno == ENOMEM ||
//		errno == EFAULT || errno == ERANGE)
//		return (1);
//	return (-1);
//}

void	ft_cd(t_sent *node, t_elst *lst)
{
	char	**tokens;
	char	current_path[DATA_SIZE];
	char	new_path[DATA_SIZE];

	tokens = node->tokens;
	if (node->tokens_len == 1)
		ft_pathcpy(lst, "HOME", new_path, DATA_SIZE);
	else if (tokens[1][0] == '-')
		ft_pathcpy(lst, "OLDPWD", new_path, DATA_SIZE);
	else if (tokens[1][0] == '~')
		cd_tilde(new_path, tokens[1], lst);
	else
		ft_strlcpy(new_path, tokens[1], DATA_SIZE);
	if (!getcwd(current_path, DATA_SIZE) || \
		chdir(new_path) == ERR_DIR_NOT_FOUND)
	{
		perror("cd");
		lst->g_exit = 1;
		return ;
	}
	ft_setenv(lst, "OLDPWD", current_path, TRUE);
	getcwd(current_path, DATA_SIZE);
	ft_setenv(lst, "PWD", current_path, TRUE);
	lst->g_exit = 0;
}
