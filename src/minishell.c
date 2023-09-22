/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:41:35 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/22 20:47:56 by sanghupa         ###   ########.fr       */
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

	ft_bzero(cmd, MAX_COMMAND_LEN);
	total_len = 0;
	if (*cmd != '\0')
		exit(EXIT_FAILURE);
	while (1)
	{
		getcmd(temp_cmd, 0, debug_mode);
		len = ft_strcspn(temp_cmd, "\n");
		if (len + total_len > MAX_COMMAND_LEN)
			exit(EXIT_FAILURE);
		if (len == 0 || temp_cmd[len - 1] != '\\')
		{
			ft_strlcat(cmd, temp_cmd, total_len + len + 1);
			total_len += len;
			break ;
		}
		ft_strlcat(cmd, temp_cmd, total_len + len);
		total_len += len;
	}
	cmd[total_len] = '\0';
	return (total_len);
}

static int	looper(char *cmd, t_elst *lst, int debug_mode)
{
	int		ret;
	t_sent	*sent;
	t_deque	*deque;

	ret = 0;
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
	ret = executecmd(deque, lst);
	sent_delall(&sent);
	deque_del(deque);
	return (ret);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		debug_mode;
	char	cmd[MAX_COMMAND_LEN];
	t_elst	*lst;

	debug_mode = FALSE;
	if (argc > 1 && (ft_strequ(argv[1], "--debug") || ft_strequ(argv[1], "-d")))
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
		if (looper(cmd, lst, debug_mode) < 0)
			break ;
	}
	env_dellst(lst);
	rl_clear_history();
	return (0);
}
