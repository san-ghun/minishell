/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:41:35 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/23 13:33:38 by minakim          ###   ########.fr       */
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

int	readcmd(char *cmd)
{
	char	temp_cmd[MAX_COMMAND_LEN];
	int		total_len;
	int		len;

	total_len = 0;
	while (1)
	{
		getcmd(temp_cmd, MAX_COMMAND_LEN);
		len = (int)ft_strcspn(temp_cmd, "\n");
		if (len > 0 && temp_cmd[len - 1] == '\\')
		{
			ft_strncpy(cmd + total_len, temp_cmd, len - 1);
			total_len += len - 1;
		}
		else
		{
			ft_strncpy(cmd + total_len, temp_cmd, len + 1);
			total_len += len + 1;
			break ;
		}
	}
	cmd[total_len - 1] = '\0';
	return (total_len - 1);
}

int	parsecmd(char *cmd, char *tokens[])
{
	int		i;
	char	*token;

	i = 0;
	token = ft_strtok(cmd, " ");
	while ((token != NULL) && (i < MAX_TOKENS))
	{
		tokens[i++] = token;
		token = ft_strtok(NULL, " ");
	}

	tokens[i] = NULL;
	return (0);
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
	char	*tokens[MAX_TOKENS];

	if (argc > 1 && argv)
		ft_putstr_fd("Invalid arguments. Try ./minishell\n", 2);
	// print_envp(envp);
	while (1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN);
		// Step 1: Accept user input
		// Create an infinite loop that continuously prompts the user for input.
		readcmd(cmd);

		// Step 2: Handle exit condition
		// Define an exit condition for the shell, such as typing "exit" 
		// or pressing a specific key combination.
		// Break the loop and exit the shell when the exit condition is met.
		if (isexit(cmd))
			break ;

		// Step 3: Parse the command
		// Split the user input into individual tokens (commands and arguments) 
		// using whitespace as a delimiter.
		// The first token represents the command, 
		// and subsequent tokens are arguments.
		parsecmd(cmd, tokens);

		// Step 4: Execute the command
		// Implement a function or a series of conditional statements 
		// to handle various commands.
		// Check the command token and execute the corresponding action or 
		// system command using libraries or system calls.
		executecmd(tokens, envp);
	}
	return (0);
}
