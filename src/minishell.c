/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:41:35 by sanghupa          #+#    #+#             */
/*   Updated: 2023/11/24 17:05:49 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	g_sigstatus;

static void	start_minishell(void)
{
	ft_putendl_fd("\n", 1);
	ft_putendl_fd("  ████████████████████████████████████████████████  ", 1);
	ft_putendl_fd("██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██", 1);
	ft_putendl_fd("██░░░░░░░░██░░██░░░░████░░░░██████░░░░████░░░░░░░░██", 1);
	ft_putendl_fd("██░░░░░░██░░██░░██░░░░██░░░░██░░░░██░░░░██░░░░░░░░██", 1);
	ft_putendl_fd("██░░░░░░██░░██░░██░░░░██░░░░██░░░░██░░░░██░░░░░░░░██", 1);
	ft_putendl_fd("██░░░░░░██░░██░░██░░░░██░░░░██░░░░██░░░░██░░░░░░░░██", 1);
	ft_putendl_fd("██░░░░░░██░░██░░██░░░░████░░██░░░░██░░░░████░░░░░░██", 1);
	ft_putendl_fd("██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██", 1);
	ft_putendl_fd("██░░░░██████░░████░░░░░░░░░░████░░░░░░░░██░░░░██░░██", 1);
	ft_putendl_fd("██░░██░░░░░░░░░░██░░░░░░░░██░░░░██░░░░██░░░░██░░░░██", 1);
	ft_putendl_fd("██░░██████░░░░░░██████░░░░████████░░░░██░░░░██░░░░██", 1);
	ft_putendl_fd("██░░░░░░░░██░░░░██░░░░██░░██░░░░░░░░░░██░░░░██░░░░██", 1);
	ft_putendl_fd("██░░████████░░░░██░░░░██░░░░██████░░██░░░░██░░░░░░██", 1);
	ft_putendl_fd("██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██", 1);
	ft_putendl_fd("  ████████████████████████████████████████████████  ", 1);
	ft_putendl_fd("\n  @sanghupa @minakim\n\n", 1);
}

static void	sighandler(int signal)
{
	t_elst		*lst;

	(void)signal;
	write(1, "\n", 1);
	if (!g_sigstatus)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	lst = ms_env();
	lst->g_exit = 130;
}

static int	looper(char *cmd, int debug_mode)
{
	int		ret;
	t_sent	*sent;
	t_deque	*deque;

	ret = 0;
	deque = deque_init();
	parsecmd(cmd, deque, debug_mode);
	sent = deque->end;
	if (debug_mode)
	{
		ft_printf("\n");
		sent_print(&sent);
		ft_printf("\n");
		ft_printf("------ result ------\n");
	}
	if (deque->size > 0)
		ret = executecmd(deque);
	sent_delall(&sent);
	deque_del(deque);
	return (ret);
}

static int	looper_wrapper(char *cmd, int debug_mode)
{
	g_sigstatus = 0;
	if (readcmd(cmd, debug_mode) < 0)
		return (-1);
	if (looper(cmd, debug_mode) < 0)
		return (-1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	static int	debug_mode;
	static int	exit_status;
	char		cmd[MAX_COMMAND_LEN];
	t_elst		*lst;

	if (argc > 1 && (ft_strequ(argv[1], "--debug") \
		|| ft_strequ(argv[1], "-d")))
		debug_mode = TRUE;
	else if (argc > 1 && argv)
	{
		ft_putstr_fd("Invalid arguments. Try ./minishell\n", 2);
		return (0);
	}
	signal(SIGCHLD, sigchldhandler);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	lst = env_to_dll(envp);
	start_minishell();
	while (1)
		if (looper_wrapper(cmd, debug_mode) < 0)
			break ;
	exit_status = lst->g_exit;
	env_dellst(lst);
	rl_clear_history();
	return (exit_status);
}
