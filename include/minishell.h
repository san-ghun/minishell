/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:39:14 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/25 23:56:18 by sanghupa         ###   ########.fr       */
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

# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "pipex.h"

// Limit Loop: use addition to while condition
# define MAX_ITER	5000

// Prevent Heap mem leak: use addition to char or array
# define DATA_SIZE	3072

// Limit length of command: 
/// @note MAX_COMMAND_LEN if running the following command in the terminal:
/// @note $ getconf ARG_MAX  // result is 2097152 (2MB).
# define MAX_COMMAND_LEN    2097152

// Limit number of tokens: 
/// @note reference from our good friend push_swap
# define MAX_TOKENS         512

/// Brief true/false notation
# define TRUE 1
# define FALSE 0

#define DIR_CHANGE_SUCCESS 0
#define ERR_DIR_NOT_FOUND -1
#define ERR_INVALID_PATH -2

/* minishell.c */

/* minishell_util.c */
void	getcmd(char *cmd, size_t len);
int		isexit(char *cmd);

/* src/util/ */
char	*ft_strpbrk(const char *str, const char *delim);
size_t	ft_strspn(const char *str, const char *delim);
char	*ft_strtok(char *str, const char *delim);
size_t	ft_strcspn(const char *str, const char *delim);
char	*ft_strncpy(char *dest, const char *src, size_t size);
char	*ft_strndup(const char *src, size_t len);
void	*ft_memalloc(size_t size);
char	*ft_strcdup(const char *src, char c);
int		ft_strequ(char const *s1, char const *s2);
int		ft_strcmp(char const *s1, char const *s2);
int		ft_isspace(char c);

// struct t_sent
/// @param token Save the cmd, its arguments, and enough to run at once, 
/// truncated by a semicolon, a pipe or a null terminated string.
/// @param is_redir indicator for 'redirect'
/// @param is_pipe indicator for 'pipe' and `;` and `\n`
/// @param is_quote indicator for the quote is open or closed
/// @param prev pointer to previous node.
/// @param next pointer to next node.
typedef struct s_sent
{
	char			*p_unit;
	int				tokens_len;
	char			**tokens;
	int				is_redir;
	int				is_pipe;
	struct s_sent	*prev;
	struct s_sent	*next;
}				t_sent;

/* src/t_sent/sent_create.c */
t_sent	*sent_new(char *p_unit, int is_redir, int is_pipe);

/* src/t_sent/sent_add.c */
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
void	deque_print_all(t_deque *deque);

/* src/parsecmd/parsecmd.c */
int		parsecmd(char *cmd, t_deque *deque);

/* src/parsecmd/parsecmd_tokenize.c */
int		get_margc(char *cmd);
char	**get_margv(char *cmd, int margc);

// struct t_env
/// @brief This struct was created with a doubly linked list
/// but can work like a deque.
/// there is a difference which is that it can be inserted and deleted
/// even if it is on an intermediate node.
/// @note Designed for env, but can be used anywhere else you need
/// to insert or delete.
/// @param key where the head of envp (i.e., before '=') is stored as 'key'
/// @param value the value of envp (i.e., after '=') is stored.
/// Both 'key' and 'value' are dynamically allocated!
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}			t_env;

/// @note For convenience, unify the internal parameter names as other.
/// @param begin front node
/// @param end rear node
typedef struct s_elst
{
	t_env	*begin;
	t_env	*end;
	int		size;
}			t_elst;

/* src/t_env/env_add */
int		env_addfront(t_elst **lst, t_env **new_node);
int		env_addrear(t_elst **lst, t_env **new_node);
int		env_addnext(t_elst **lst, t_env **current, t_env **new_node);
void	env_add_or_update(t_elst *data, char *key, char *value);
/* src/t_env/env_init */
void	env_updatesize(t_elst *lst, int add);
t_env	*env_newnode(char *key, char *value);
t_elst	*env_initdll(void);

/* src/t_env/env_del */
int		env_reset_node(t_env *node_to_delete);
int		env_delone(t_elst *list, t_env *node_to_delete);
void	env_dellst(t_elst *lst);

/* src/built-in/ft_echo */
void	ft_echo(t_sent *node);

/* src/built-in/ft_env */
t_elst	*env_to_dll(char **envp);
char	*pathjoin(t_env *node);
char	**dll_to_envp(t_elst *lst);

/*src/built-in/ft_cd */

#endif
