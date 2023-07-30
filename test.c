/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:15:06 by minakim           #+#    #+#             */
/*   Updated: 2023/07/30 14:49:48 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	main(int argc, char *argv[], char *envp[])
//{
//	//test : ft_strtok
//	char s1[] = "This !is !the !way.";
//	char d[] = " !";
//
//	char *portion1 = ft_strtok(s1, d);
//	ft_printf("--ft_strtok--\n");
//	ft_printf("%s\n", portion1);
//	portion1 = ft_strtok(NULL, d);
//	ft_printf("%s\n", portion1);
//	portion1 = ft_strtok(NULL, d);
//	ft_printf("%s\n", portion1);
//	portion1 = ft_strtok(NULL, d);
//	ft_printf("%s\n", portion1);
//	portion1 = ft_strtok(NULL, d);
//	ft_printf("%s\n", portion1);
//
//	char s2[] = "This !is !the !way.";
//	char *portion2 = strtok(s2, d);
//	ft_printf("\n--strtok--\n");
//	ft_printf("%s\n", portion2);
//	portion2 = strtok(NULL, d);
//	ft_printf("%s\n", portion2);
//	portion2 = strtok(NULL, d);
//	ft_printf("%s\n", portion2);
//	portion2 = strtok(NULL, d);
//	ft_printf("%s\n", portion2);
//	portion2 = strtok(NULL, d);
//	ft_printf("%s\n", portion2);
//
//	return (0);
//}

static int count_semi(char *cmd)
{
	int		i;
	int		count;
	uint8_t	quotes;

	count = 1;
	quotes = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '"')
			quotes ^= 1;
		else if (cmd[i] == ';' && !quotes)
			count++;
	}
	return (count);
}

t_deque	*parse_cmd_to_list(char *cmd, t_deque *lst)
{
	t_sent	*new;
	int 	size;
	int 	i;
	int 	j;

	size = count_semi(cmd);
	i = -1;
	j = -1;
	while (++i < size)
	{
		j++;
		new = sent_new(ft_strcdup(&cmd[j], ';'), 0, 0);
		while(cmd[j] && cmd[j] != ';')
			j++;
		new = new->next;
	}
	lst->begin = sent_getfront(new);
	lst->end = sent_getlast(new);
	lst->size = size;
	return (lst);
}

t_deque *print_all_test(t_deque *lst)
{
	t_sent *node;

	node = lst->begin;
	while(node != NULL)
	{
		ft_printf("%s\n", node->cmd);
		node = node->next;
	}
}

size_t	readcmd_test(char *cmd)
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


int	main(int ac, char **av)
{
	t_deque lst;
	char	cmd[MAX_COMMAND_LEN];

	readcmd_test(cmd);
	parse_cmd_to_list(cmd, &lst);
	print_all_test(&lst);
}