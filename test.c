/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:15:06 by minakim           #+#    #+#             */
/*   Updated: 2023/09/02 10:39:21 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"
#include <assert.h>

void ft_print_env(t_env *node)
{
	printf("%s=%s\n", node->key, node->value);
}

void tmp_print_all(t_elst *lst)
{
	t_env *node;
	int i = -1;

	node = lst->begin;
	printf("------- start --------\n");
	while (node != NULL)
	{
		ft_print_env(node);
		node = node->next;
	}
	printf("------- done --------\n");
}

size_t	readcmd(char *cmd)
{
	size_t	len;
	size_t	total_len;
	char	temp_cmd[MAX_COMMAND_LEN];

	total_len = 0;
	ft_strlcpy(cmd, "", 2);
	if (*cmd != '\0')
		exit(EXIT_FAILURE);
	total_len = ft_strlen(cmd);
	while (1)
	{
		getcmd(temp_cmd, 0);
		len = ft_strcspn(temp_cmd, "\n");
		if (len == 0 || temp_cmd[len - 1] != '\\')
		{
			ft_strlcat(cmd, temp_cmd, ft_strlen(cmd) + len + 1);
			break ;
		}
		ft_strlcat(cmd, temp_cmd, ft_strlen(cmd) + len);
	}
	total_len = ft_strlen(cmd);
	cmd[total_len] = '\0';
	return (total_len);
}

int main(int ac, char **av, char **envp)
{
	char cmd[MAX_COMMAND_LEN];
	t_elst *lst = env_to_dll(envp);

	while (1)
	{
		printf("minishell> ");
		readcmd(cmd);
		printf("cmd: %s\n", cmd);
		char **test = ft_split(cmd, ' ');
		int size = 0;
		while (test[size])
			size++;
		printf("Current directory before cd: %s\n", getcwd(NULL, 0));
		ft_cd(test, size, lst);
		printf("Current directory after cd: %s\n", getcwd(NULL, 0));
	}
	env_dellst(lst);
	return (0);
}