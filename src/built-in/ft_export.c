/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:32:14 by minakim           #+#    #+#             */
/*   Updated: 2023/10/04 18:47:55 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @note
void	ft_export(t_sent *node, t_elst *lst);

static int	export_error(char *cmd)
{
	char	command[DATA_SIZE];
	char	*msg;

	ft_strlcpy(command, "bash: export: `", DATA_SIZE);
	ft_strlcat(command, cmd, DATA_SIZE);
	msg = ft_strdup("': not a valid identifier\n");
	ft_strlcat(command, msg, DATA_SIZE);
	ms_env()->g_exit = 1;
	ms_error(command);
	free(msg);
	return (1);
}

int	is_key(char *key)
{
	if (!ft_isalpha(*key))
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

void	ft_export(t_sent *node, t_elst *lst)
{
	char	*key;
	char	*value;
	char	*separator;

	if (node->tokens_len == 1)
		ft_env(node, lst);
	else if (node->tokens_len > 1)
	{
		separator = ft_strpbrk(node->tokens[1], "=");
		if (separator)
		{
			key = ft_substr(node->tokens[1], 0, separator - node->tokens[1]);
			value = ft_strdup(separator + 1);
			if (is_key(key) && ft_setenv(lst, key, value, TRUE) == 0)
				lst->g_exit = 0;
			else
				export_error(node->tokens[1]);
			free(key);
			free(value);
		}
		else
			export_error(node->tokens[1]);
	}
}
