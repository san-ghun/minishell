/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:40:09 by minakim           #+#    #+#             */
/*   Updated: 2023/10/22 11:41:40 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @note
void	ft_unset(t_sent *node, t_elst *lst);

static int	unset_error(char *cmd)
{
	char	command[DATA_SIZE];
	char	*msg;

	ft_strlcpy(command, "미쉘: unset: `", DATA_SIZE);
	ft_strlcat(command, cmd, DATA_SIZE);
	msg = ft_strdup("': not a valid identifier\n");
	ft_strlcat(command, msg, DATA_SIZE);
	ms_env()->g_exit = 1;
	write(STDERR_FILENO, command, ft_strlen(command));
	free(msg);
	return (1);
}

int	ft_unsetenv(char *key, t_elst *lst)
{
	t_env	*tmp;

	tmp = lst->begin;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
		{
			env_delone(lst, tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_unset(t_sent *node, t_elst *lst)
{
	char	*key;
	int		fd;
	int		i;

	i = 1;
	fd = redi_out(node);
	if (node->tokens_len > 1)
	{
		while (node->tokens[i])
		{
			key = node->tokens[i];
			if (!ft_unsetenv(key, lst))
				unset_error(node->tokens[i]);
			i++;
		}
	}
	if (fd != 1)
		close(fd);
	lst->g_exit = 0;
}
