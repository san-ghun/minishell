/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:35:32 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/20 17:12:24 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *argv, int option)
{
	int	file;

	file = 0;
	if (option == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (option == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (option == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		ft_error();
	return (file);
}

void	waiting_child(int fd[2], int pid)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	if (pid == 0)
		wait(NULL);
	else
		waitpid(pid, NULL, 0);
}

void	child_process(char *argv, char *envp[])
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_error();
	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_exec(&argv, envp);
	}
	else
		waiting_child(fd, pid);
}

void	heredoc(char *limiter, int argc)
{
	int		fd[2];
	char	*line;
	pid_t	reader;

	if (argc < 6)
		instruction();
	if (pipe(fd) == -1)
		ft_error();
	line = "";
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
		waiting_child(fd, 0);
}
/*
int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			fileout = open_file(argv[argc - 1], 0);
			heredoc(argv[2], argc);
			i = 3;
		}
		else
		{
			fileout = open_file(argv[argc - 1], 1);
			filein = open_file(argv[1], 2);
			dup2(filein, STDIN_FILENO);
			i = 2;
		}
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		ft_exec(argv[argc - 2], envp);
	}
	instruction();
}
*/
