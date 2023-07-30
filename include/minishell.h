/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:39:14 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/30 13:49:13 by minakim          ###   ########.fr       */
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

// macro
# include "macro.h"

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

// Limit length of command: 
/// @note MAX_COMMAND_LEN if running the following command in the terminal:
/// @note $ getconf ARG_MAX  // result is 2097152 (2MB).
# define MAX_COMMAND_LEN    2097152

// Limit number of tokens: ...
# define MAX_TOKENS         10

/* minishell.c */

/* minishell_util.c */
void	getcmd(char *cmd, size_t len);
int		isexit(char *cmd);

/* parse_cmd_to_list */
t_deque	*parse_cmd_to_list(char *cmd, t_deque *lst);


/* src/util/ */
char	*ft_strpbrk(const char *str, const char *delim);
size_t	ft_strspn(const char *str, const char *delim);
char	*ft_strtok(char *str, const char *delim);
size_t	ft_strcspn(const char *str, const char *delim);
char	*ft_strncpy(char *dest, const char *src, size_t size);
void	*ft_memalloc(size_t size);
char	*ft_strcdup(const char *src, char c);

// struct t_sent
/// @param cmd Save the cmd, its arguments, and enough to run at once,
/// truncated by a semicolon.
/// @param tok Store the tokenised result by checking the prefix and suffix.
/// @param prefix indicator for prefix type such as, 'redirect' 'pipe' ...
/// @param suffix indicator for suffix type such as, 'redirect' 'pipe' ...
/// @param prev pointer to previous node.
/// @param next pointer to next node.
typedef struct s_sent
{
	char				*cmd;
	char 				**tok;
	int					prefix;
	int					suffix;
	struct s_sent		*prev;
	struct s_sent		*next;
}				t_sent;

/* src/t_sent/sent_create.c */
t_sent	*sent_new(char *cmd, int prefix, int suffix);
void	sent_addfront(t_sent *sent[], t_sent *new);
void	sent_addback(t_sent *sent[], t_sent *new);

/* src/t_sent/sent_read.c */
t_sent	*sent_getone(t_sent *sent[], char *cmd);
t_sent	*sent_getlast(t_sent *sent);
t_sent	*sent_getfront(t_sent *sent);


/* src/t_sent/sent_update.c */
void	sent_update(t_sent *sent[], char *old, char *new);

/* src/t_sent/sent_delete.c */
void	sent_del(t_sent *sent);
void	sent_delone(t_sent *sent[], t_sent *target);
void	sent_delall(t_sent *sent[]);

/* src/t_sent/sent_util.c */
size_t	sent_len(t_sent *sent[]);
void	sent_print(t_sent *sent[]);


// struct t_deque
typedef struct s_deque
{
	struct s_sent	*begin;
	struct s_sent	*end;
	int				size;
}					t_deque;

/* src/deque/deque_create.c */
t_deque	*deque_init(void);
void	deque_push_front(t_deque *deque, t_sent *new);
void	deque_push_back(t_deque *deque, t_sent *new);

/* src/deque/deque_read.c */
t_sent	*deque_at(t_deque *deque, int index);

/* src/deque/deque_update.c */
void	deque_update(t_deque *deque, t_sent *old, t_sent *new);

/* src/deque/deque_delete.c */
void	deque_del(t_deque *deque);
t_sent	*deque_pop_front(t_deque *deque);
t_sent	*deque_pop_back(t_deque *deque);

/* src/deque/deque_util.c */
size_t	deque_size(t_deque *deque);
int		deque_isempty(t_deque *deque);
t_sent	*deque_front(t_deque *deque);
t_sent	*deque_back(t_deque *deque);

#endif
