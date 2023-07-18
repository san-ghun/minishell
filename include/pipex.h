/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:34:19 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/18 14:41:19 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// open 
# include <fcntl.h>

// close read write access dup dup2 execve exit fork pipe unlink 
# include <unistd.h>

// malloc free 
# include <stdlib.h>

// perror
# include <stdio.h>

// strerror
# include <string.h>

// wait waitpid
# include <sys/wait.h>

# include "libft.h"
# include "ft_printf.h"

# include <ctype.h>

/* pipex.c */
int		open_file(char *argv, int option);
void	waiting_child(int fd[2], int pid);
void	child_process(char *argv, char *envp[]);
void	heredoc(char *limiter, int argc);

/* pipex_util.c */
char	*find_path(char *cmd, char *envp[]);
void	ft_error(void);
void	ft_exec(char *arg, char *envp[]);
void	instruction(void);
int		get_line(char *line[]);

#endif
