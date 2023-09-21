/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:11:49 by minakim           #+#    #+#             */
/*   Updated: 2023/09/17 20:46:23 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <assert.h> /// 나중에 제거하기 !


/**
 * @brief This function converts the envp array to a Doubly Linked List (DLL).
 * The DLL uses t_env as its node, where the head of envp (i.e., before '=')
 * is stored as 'key' and the value (i.e., after '=') is stored as 'value'.
 * Both 'key' and 'value' are dynamically allocated!
 * @return If successfully converted, it returns the lst. Otherwise, it triggers
 * an assert message (temporary). Note that error handling isn't fully
 * implemented, so an update is required after the "else" clause.
 * @note The node initialization is verbose for the sake of fewer lines.
 * Further explanations will be provided in meetings.
 */
t_elst	*env_to_dll(char **envp)
{
	int		i;
	char	*separator;
	t_elst	*lst;
	t_env	*node;

	lst = env_init();
	i = -1;
	while (envp[++i])
	{
		separator = ft_strpbrk(envp[i], "=");
		if (separator)
		{
			node = env_newnode(ft_substr(envp[i], 0, separator - envp[i]), \
			ft_strdup(separator + 1));
			env_addrear(&lst, &node);
		}
		else
		{
			assert("error handling needed here");
			env_dellst(lst);
			return (NULL);
		}
	}
	return (lst);
}

/// @brief combines a KEY and a VALUE in the form `KEY=VALUE`.
/// The function returns a memory-allocated result.
char	*pathjoin(t_env *node)
{
	char	*path;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(node->key);
	value_len = ft_strlen(node->value);
	path = ft_memalloc( key_len + 1 + value_len + 1);
	if (!path)
		return (NULL);
	ft_strlcpy(path, node->key, key_len + 1);
	path[key_len] = '=';
	ft_strlcpy(path + key_len + 1, node->value, value_len + 1);
	return (path);
}

char	**dll_to_envp(t_elst *lst)
{
	t_env	*node;
	char	**envp;
	int		i;

	envp = ft_memalloc(sizeof(char *) * (lst->size + 1));
	if (!envp)
		return (NULL);
	node = lst->begin;
	i = 0;
	while (node != NULL && i < lst->size)
	{
		envp[i] = pathjoin(node);
		if (envp[i] == NULL)
			assert("error\n");
		node = node->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

/// @brief combines a KEY and a VALUE in the form `KEY=VALUE` to @param path
void	pathjoin_print(char *path, t_env *node)
{
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(node->key);
	value_len = ft_strlen(node->value);

	ft_strlcpy(path, node->key, key_len + 1);
	path[key_len] = '=';
	ft_strlcpy(path + key_len + 1, node->value, value_len + 1);
}


void	ft_env(t_sent *node, t_elst *lst)
{

	t_env	*env;
	char	path[DATA_SIZE];
	int		fd;

	fd = redi_out(node);
	env = lst->begin;
	if (node->tokens_len == 1)
	{
		while (env != NULL)
		{
			pathjoin_print(path, env);
			ft_putendl_fd(path, fd);
			env = env->next;
		}
		lst->g_exit = 0;
	}
	else
		lst->g_exit = 1;
	if (fd != 1)
		close(fd);
}

void	ft_pwd(t_sent *node, t_elst *lst)
{
	static char	pwd[DATA_SIZE];
	int		fd;

	fd = redi_out(node);
	if (node->tokens_len > 1)
	{
		ft_printf("error\n");
		lst->g_exit = 1; // tmp error status
		return ;
	}
	else if (getcwd(pwd, DATA_SIZE))
	{
		ft_putendl_fd(pwd, fd);
		lst->g_exit = 0;
	}
	else
	{
		ft_printf("pwd: error retrieving current directory\n");
		lst->g_exit = 1; // tmp error status
	}
	if (fd != 1)
		close(fd);
}
