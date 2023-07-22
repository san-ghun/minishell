/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:39:14 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/22 14:36:13 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// close read write access dup dup2 execve fork pipe unlink 
// STDIN_FILENO STDOUT_FILENO getcwd chdir isatty ttyname ttyslot
# include <unistd.h>

// malloc free exit getenv
# include <stdlib.h>

// printf perror
# include <stdio.h>

// opendir readdir closedir
# include <dirent.h>

// open O_RDONLY O_WRONLY O_RDWR O_CREAT O_TRUNC
# include <fcntl.h>

// errno EACCES ENOENT
# include <errno.h>

// strerror
# include <string.h>

// readline
# include <readline/readline.h>

// add_history clear_history
# include <readline/history.h>

// signal kill SIGINT SIGQUIT sigaction sigemptyset sigaddset
# include <signal.h>

// wait waitpid wait3 wait4
# include <sys/wait.h>

// stat lstat fstat 
# include <sys/stat.h>

// ioctl 
# include <sys/ioctl.h>

// tcsetattr tcgetattr
# include <termios.h>

// tgetent tgetflag tgetnum tgetstr tgoto tputs
# include <curses.h>
# include <term.h>

# include "libft.h"
# include "ft_printf.h"
# include "pipex.h"

// Limit Loop: use addition to while condition
# define MAX_ITER	5000

// Prevent Heap mem leak: use addition to char or array
# define DATA_SIZE	3072


//Limiter for command and tokens
//MAX_COMMAND_LEN if running the following command in the terminal:
//$ getconf ARG_MAX
//result is 2097152 (2MB).
# define MAX_COMMAND_LEN 100 //2097152
# define MAX_TOKENS 10

/* minishell.c */

/* minishell_util.c */
void	getcmd(char *cmd, int len);
int		isexit(char *cmd);


/* ft_strtok.c */
char	*ft_strpbrk(const char *str, const char *delim);
size_t	ft_strspn(const char *str, const char *delim);
char	*ft_strtok(char *str, const char *delim);

/* ft_strcspn.c.c */
size_t	ft_strcspn(const char *str, const char *delim);

/* ft_strncpy.c */
char *ft_strncpy(char *dest, const char *src, size_t size);

#endif
