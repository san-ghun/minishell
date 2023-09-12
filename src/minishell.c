/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:41:35 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/12 21:53:24 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	looper(char *cmd, char *envp[], t_elst *lst, int debug_mode)
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
		looper(cmd, envp, lst, debug_mode);
	}
	env_dellst(lst);
	return (0);
}
