/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:32:14 by minakim           #+#    #+#             */
/*   Updated: 2023/11/24 16:20:16 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @note
void	ft_export(t_sent *node, t_elst *lst);

static int	export_error(char *cmd)
{
	char	command[DATA_SIZE];
	char	*msg;

	ft_strlcpy(command, "미쉘: export: `", DATA_SIZE);
	ft_strlcat(command, cmd, DATA_SIZE);
	msg = ft_strdup("': not a valid identifier\n");
	ft_strlcat(command, msg, DATA_SIZE);
	ms_env()->g_exit = 1;
	free(msg);
	write(STDERR_FILENO, command, ft_strlen(command));
	return (1);
}

int	is_key(char *key)
{
	if (key[0] == '_' && key[1] == '\0')
		return (3);
	if (ft_isalpha(*key) || *key == '_')
		key++;
	else
		return (0);
	while (*key)
	{
		if (ft_isalnum(*key) || *key == '_')
			key++;
		else
			return (0);
	}
	return (1);
}

char	*set_value(char *separator)
{
	char	*value;

	value = NULL;
	if (separator[1] == '\0')
		value = ft_strdup(" ");
	else
		value = ft_strdup(separator + 1);
	return (value);
}

void	check_and_set(t_sent *node, t_elst *lst, char *separator, int i)
{
	char	*key;
	char	*value;
	int		check_key;

	key = NULL;
	value = NULL;
	key = ft_substr(node->tokens[i], 0, separator - node->tokens[i]);
	value = set_value(separator);
	check_key = is_key(key);
	if (check_key > 0)
	{
		if (check_key == 3)
			lst->g_exit = 0;
		if (check_key == 1)
		{
			if (ft_setenv(lst, key, value, TRUE) == 0)
				lst->g_exit = 0;
		}
	}
	else
		export_error(node->tokens[i]);
	free(key);
	free(value);
}

void	ft_export(t_sent *node, t_elst *lst)
{
	char	*separator;
	int		i;

	i = 0;
	if (node->tokens_len == 1)
		ft_env(node, lst);
	else if (node->tokens_len > 1)
	{
		while (node->tokens[++i])
		{
			separator = NULL;
			separator = ft_strpbrk(node->tokens[i], "=");
			if (separator)
				check_and_set(node, lst, separator, i);
			else
				if (is_key(node->tokens[i]) < 1)
					export_error(node->tokens[i]);
		}
	}
}
