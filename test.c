/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:03:20 by minakim           #+#    #+#             */
/*   Updated: 2023/09/12 22:26:26 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

static void	sighandler(int signal)
{
	(void)signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

size_t	readcmd(char *cmd, int debug_mode)
{
	size_t	len;
	size_t	total_len;
	char	temp_cmd[MAX_COMMAND_LEN];

	total_len = 0;
	ft_bzero(cmd, MAX_COMMAND_LEN);
	if (*cmd != '\0')
		exit(EXIT_FAILURE);
	total_len = ft_strlen(cmd);
	while (1)
	{
		getcmd(temp_cmd, 0, debug_mode);
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

/// built-in functions check
typedef struct s_cmd
{
	char	*cmd_name;
	void	(*cmd_func)(t_sent *node, t_elst *lst);
}				t_cmd;

static int	dispatchcmd(t_sent *node, t_elst *lst)
{
	static t_cmd	cmd_table[] = {
			{"cd", ft_cd},
			{"echo", ft_echo},
			{"pwd", ft_pwd},
			{"env", ft_env},
			{NULL, NULL}};
	int				i;

	i = -1;
	while (cmd_table[++i].cmd_name)
	{
		if (ft_strequ(node->tokens[0], cmd_table[i].cmd_name))
		{
			cmd_table[i].cmd_func(node, lst);
			return (1);
		}
	}
	return (0);
}

/// TMP FUNCTION.
void	free_mevnp(char **menvp)
{
	int i;

	i = -1;
	while(menvp[++i])
		free(menvp[i]);
	free(menvp);
	menvp = NULL;
}

void	execute_node(t_sent *node, t_elst *lst)
{
	pid_t	pid;
	char	**menvp; // edited

	pid = fork();
	if (pid < 0)
	{
		perror("Error");
		ft_putstr_fd("Failed to fork\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (node->tokens[0] == NULL)
			exit(EXIT_SUCCESS);
		if (dispatchcmd(node, lst)) // edited
			exit(EXIT_SUCCESS);
		menvp = dll_to_envp(lst); // edited
		ft_exec(node->tokens, menvp); // edited
		free_mevnp(menvp); /// edited
		perror("Error");
		ft_putstr_fd("Failed to execute command\n", 2);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
}

/// I've marked the parts I've edited.
void	executecmd(t_deque *deque, t_elst *lst)
{
	t_sent	*node;

	while (0 < deque->size)
	{
		node = deque_pop_back(deque);
		execute_node(node, lst);
	}
	return ;
}

static void	looper(char *cmd, t_elst *lst, int debug_mode)
{
	t_sent	*sent;
	t_deque	*deque;

	deque = deque_init();
	parsecmd(cmd, deque, lst, debug_mode);
	sent = deque->end;

	if (debug_mode)
	{
		ft_printf("\n");
		sent_print(&sent);
		ft_printf("\n");
		ft_printf("------ result ------\n");
	}

	executecmd(deque, lst);
	sent_delall(&sent);
	deque_del(deque);
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	int		debug_mode;
	char	cmd[MAX_COMMAND_LEN];
	t_elst	*lst;

	debug_mode = FALSE;
	if (ft_strequ(argv[1], "--debug") || ft_strequ(argv[1], "-d"))
		debug_mode = TRUE;
	else if (argc > 1 && argv)
	{
		ft_putstr_fd("Invalid arguments. Try ./minishell\n", 2);
		return (0);
	}
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	lst = env_to_dll(envp);
	while (1)
	{
		readcmd(cmd, debug_mode);
		if (isexit(cmd))
			break ;
		looper(cmd, lst, debug_mode);
	}
	env_dellst(lst);
	return (0);
}
