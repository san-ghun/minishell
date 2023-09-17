/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:12:54 by minakim           #+#    #+#             */
/*   Updated: 2023/09/17 20:14:51 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_heredoc(char *cmd, t_elst *elst)
{
	char	str[MAX_COMMAND_LEN];
	int		i;

	ft_bzero(&str[0], MAX_COMMAND_LEN);
	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$')
			i += append_env(&str[0], &cmd[i], elst);
		else
			ft_strlcat(&str[0], &cmd[i], ft_strlen(str) + 2);
		i++;
	}
	ft_strlcpy(cmd, str, ft_strlen(str) + 1);
	return ;
}

// implement heredoc handling and execution
void	flag_heredoc(t_sent *node, t_elst *lst)
{
	char	*line;
	char	*end_marker;
	int		fd[2];

	(void) lst;
	end_marker = node->input_argv;
	pipe(fd);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strequ(line, end_marker))
		{
			free(line);
			break;
		}
		expand_cmd(line, lst);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);

}

// implement input redirection read handling and execution
void flag_redi_read(t_sent *node, t_elst *lst)
{
	int		fd;
	char	*filename;

	(void)lst;
	filename = node->input_argv;
	fd = open_file(filename, 2);
	if (fd == -1)
		return;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

// Implement output redirection write append handling and execution
void flag_redi_append(t_sent *node, t_elst *lst)
{
	(void) lst;
	int fd;
	char *filename;

	filename = node->output_argv;
	fd = open_file(filename, 0);
	if (fd == -1)
		return;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

// Implement output redirection write trunc handling and execution
void flag_redi_trunc(t_sent *node, t_elst *lst)
{
	(void) lst;
	int fd;
	char *filename;

	filename = node->output_argv;
	fd = open_file(filename, 1);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}