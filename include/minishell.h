/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:39:14 by sanghupa          #+#    #+#             */
/*   Updated: 2023/11/10 01:10:25 by minakim          ###   ########.fr       */
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
//# define MAX_COMMAND_LEN    2097152
# define MAX_COMMAND_LEN    3072

// Limit number of tokens: 
/// @note reference from our good friend push_swap
# define MAX_TOKENS         512

// Limit number of env key name:
# define MAX_KEY_VAR		255

/// @note Brief true/false notation
# define TRUE 1
# define FALSE 0

/// @note Brief branching point notation in process
# define CHILD 1
# define PARENT 2

/// @note max pipes size
# define MAX_PIPES 200

# define ERR_DIR_NOT_FOUND -1

/// @note FLAGS
// STDIN_FILENO == 0
// STDOUT_FILENO == 1
// STDERR_FILENO == 2
# define PIPE_FLAG 3
# define REDI_WR_APPEND_FLAG 4
# define REDI_WR_TRUNC_FLAG 5
# define REDI_RD_FLAG 6
# define HDOC_FLAG 7

/* minishell.c */
extern uint8_t	g_sigstatus;

/* minishell_util.c */
int		isexit(char *cmd);
int		ms_error(char *msg);
void	sigchldhandler(int signo);

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
int		ft_strnequ(char const *s1, char const *s2, size_t i);

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
	int				input_flag;
	int				output_flag;
	char			*input_argv;
	char			*output_argv;
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
/// @var g_exit adding it here
/// because the global variables have become unavailable.
typedef struct s_elst
{
	t_env	*begin;
	t_env	*end;
	int		size;
	int		g_exit;
}			t_elst;

/* src/t_env/env_add */
int		env_addfront(t_elst **lst, t_env **new_node);
int		env_addrear(t_elst **lst, t_env **new_node);
int		env_addnext(t_elst **lst, t_env **current, t_env **new_node);

/* src/t_env/env_init */
void	env_updatesize(t_elst *lst, int add);
t_env	*env_newnode(char *key, char *value);
t_elst	*env_init(void);
t_elst	*ms_env(void);

/* src/t_env/env_del */
void	env_del(t_env *target);
void	env_delone(t_elst *lst, t_env *target);
void	env_dellst(t_elst *lst);

/* src/t_env/env_util */
int		ft_setenv(t_elst *lst, const char *key, \
					const char *value, int overwrite);
char	*ft_getenv(t_elst *lst, char *key);

/// built-in.folder
/* src/built-in/ft_echo */
void	ft_echo(t_sent *node, t_elst *lst);
int		redi_out(t_sent *node);

/* src/built-in/ft_env */
void	ft_env(t_sent *node, t_elst *lst);
t_elst	*env_to_dll(char **envp);
char	*pathjoin(t_env *node);
char	**dll_to_envp(t_elst *lst);

/*src/built-in/ft_cd */
void	ft_cd(t_sent *node, t_elst *lst);

/*src/built-in/ft_export */
void	ft_export(t_sent *node, t_elst *lst);

/*src/built-in/ft_unset */
void	ft_unset(t_sent *node, t_elst *lst);

/*src/built-in/ft_pwd */
void	ft_pwd(t_sent *node, t_elst *lst);

/*src/built-in/ft_exit */
void	ft_exit(t_sent *node, t_elst *lst);

/// readcmd
/* src/readcmd/readcmd.c */
int		readcmd(char *cmd, int debug_mode);

/// parsecmd
/* src/parsecmd/parsecmd.c */
int		parsecmd(char *cmd, t_deque *deque, int debug_mode);

/* src/parsecmd/parsecmd_tokenize.c */
int		get_margc(char *cmd);
char	**get_margv(char *cmd, int margc);

/* src/parsecmd/parsecmd_tosent.c */
int		split_cmd(t_sent *node, char *margv[], int select, int i);

/* src/parsecmd/parsecmd_util.c */
int		check_quotes(char *cmd, int index, int status);
void	expand_cmd(char *cmd);
int		append_env(char *str, char *cmd);
int		ms_strndup_helper(const char *src, char *new, int len);

typedef enum e_mode{
	NONE,
	INPUT,
	OUTPUT
}		t_mode;

/// execute
typedef struct s_ctx
{
	int		old_fd[2];
	int		fd[2];
	int		pids[MAX_PIPES];
	int		i;
	int		wait_count;
	int		cmd_count;
	int 	first_cmd;
}				t_ctx;

t_ctx	*ms_ctx(void);

/* src/executecmd/executecmd.c */
int		executecmd(t_deque *deque);
int		ft_execvp(t_sent *cmd);
void	add_wait_count(int pid);
void	close_fds(t_sent *cmd, t_deque *deque, t_ctx *c);
void	update_fd(t_deque *deque, t_ctx *c);

/* src/executecmd/executecmd_process.c */
int		run_process(t_sent *cmd, t_deque *deque);

/* src/executecmd/executecmd_util.c */
void	ft_ms_exit(t_sent *cmd, t_deque *deque, int exit_code);
t_ctx	*ms_ctx(void);

/* src/executecmd/executecmd_flag_handler.c */
int		run_by_flag(t_sent *cmd, t_mode flag);

/// dispatch
typedef struct s_cmd
{
	char	*cmd_name;
	void	(*cmd_func)(t_sent *node, t_elst *lst);
}				t_cmd;

/* src/executecmd/executecmd_dispatch_handler.c */
int		dispatchcmd_wrapper(t_sent *cmd, int where);
int		is_built_in(t_sent *cmd);

/* src/executecmd/executecmd_dispatch_handler_util.c */
t_cmd	*builtins_child(void);
t_cmd	*builtins_parent(void);

/// list of executable flags
/* src/executecmd/runheredoc.c */
int		flag_heredoc(t_sent *node, t_elst *lst);

/* src/executecmd/heredoc.c */
typedef struct s_hdoc
{
	char	*line;
}			t_hdoc;

t_hdoc	*hdoc(void);

/* src/executecmd/runredi.c */
int		flag_redi_read(t_sent *node, t_elst *lst);
int		flag_redi_append(t_sent *node, t_elst *lst);
int		flag_redi_trunc(t_sent *node, t_elst *lst);

/* src/executecmd/executecmd_util.c */
void	ft_free_2d(char **targets);
int		ft_free_check(char *path, char *menvp[], int ret);
char	*ms_find_path(char *cmd);
int		ft_free_exit(char *path, char *menvp[], int ret);

/* src/executecmd/executecmd_check.c */
int		check_path(char *path, char *cmd);
int		check_pid(pid_t pid);

/* src/util/ms_split.c */
size_t	ms_split_size(char const *s, char c);
char	**ms_split_process(char const *s, char c, char **tmp, size_t i);
char	**ms_split(char const *s, char c);

#endif
