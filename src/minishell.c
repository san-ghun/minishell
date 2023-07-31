/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:41:35 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/31 17:37:26 by minakim          ###   ########.fr       */
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

//int	parsecmd_save(char *cmd, char *tokens[])
//{
//	int		i;
//	char	*token;
//
//	i = 0;
//	token = ft_strtok(cmd, " ");
//	while ((token != NULL) && (i < MAX_TOKENS))
//	{
//		tokens[i++] = token;
//		token = ft_strtok(NULL, " ");
//	}
//	tokens[i] = NULL;
//	return (0);
//}

int parsecmd(char *cmd, t_deque *lst)
{
	parse_cmd_to_list(cmd, lst);
	// parse start
	// tokenise ();
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
	t_deque	lst;

	(void)envp;
	(void)tokens;
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
		parsecmd(cmd, &lst);

		// Step 4: Execute the command
		// Implement a function or a series of conditional statements 
		// to handle various commands.
		// Check the command token and execute the corresponding action or 
		// system command using libraries or system calls.
		// executecmd(tokens, envp);

		sent_delall(&lst.begin);
	}
	return (0);
}
