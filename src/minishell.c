/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:41:35 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/02 11:02:30 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	print_envp(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("envp %d = %s\n", i, envp[i]);
		i++;
	}
}
*/

static void	sighandler(int signal)
{
	(void)signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

size_t	readcmd(char *cmd)
{
	size_t	len;
	size_t	total_len;
	char	temp_cmd[MAX_COMMAND_LEN];

	total_len = 0;
	ft_strlcpy(cmd, "", 2);
	if (*cmd != '\0')
		exit(EXIT_FAILURE);
	total_len = ft_strlen(cmd);
	while (1)
	{
		getcmd(temp_cmd, 0);
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

void	executecmd(char *tokens[], char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error");
		ft_putstr_fd("Failed to fork\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (tokens[0] == NULL)
			exit(EXIT_SUCCESS);
		ft_exec(tokens, envp);
		perror("Error");
		ft_putstr_fd("Failed to execute command\n", 2);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	cmd[MAX_COMMAND_LEN];
	// char	*tokens[MAX_TOKENS];
	t_deque	*deque;
	t_elst	*lst;

	(void)envp;
	if (argc > 1 && argv)
		ft_putstr_fd("Invalid arguments. Try ./minishell\n", 2);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		// Step 1: Accept user input
		// Create an infinite loop that continuously prompts the user for input.
		readcmd(cmd);

		// Step 2: Handle exit condition
		// Define an exit condition for the shell, such as typing "exit" 
		// or pressing a specific key combination.
		// Break the loop and exit the shell when the exit condition is met.
		if (isexit(cmd))
			break ;

		deque = deque_init();
		lst = env_to_dll(envp);

		// Step 3: Parse the command
		// Split the user input into individual tokens (commands and arguments) 
		// using whitespace as a delimiter.
		// The first token represents the command, 
		// and subsequent tokens are arguments.
		parsecmd(cmd, deque, envp);

		ft_printf("\n");
		sent_print(&deque->end);
		ft_printf("\n");
		deque_print_all(deque);

		// Step 4: Execute the command
		// Implement a function or a series of conditional statements 
		// to handle various commands.
		// Check the command token and execute the corresponding action or 
		// system command using libraries or system calls.
		// executecmd(tokens, envp);

		sent_delall(&deque->end);
		deque_del(deque);
	}
	return (0);
}
