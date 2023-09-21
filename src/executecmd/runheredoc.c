/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runheredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:14:32 by minakim           #+#    #+#             */
/*   Updated: 2023/09/18 18:55:08 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_env_key(char *ptr, char *env_name)
{
	int	i;

	i = 0;
	while (ptr[i] && !ft_isspace(ptr[i]) && ptr[i] != '\n' && i < MAX_KEY_VAR)
	{
		env_name[i] = ptr[i];
		i++;
	}
	env_name[i] = '\0';
	return (ptr + i);
}

static char	*replace_with_env_value(char *bptr, char *env_name, t_elst *lst)
{
	char	*env_value;

	env_value = ft_getenv(lst, env_name);
	if (env_value)
	{
		ft_strncpy(bptr, env_value, ft_strlen(env_value));
		bptr += ft_strlen(env_value);
	}
	return (bptr);
}

char	*replace_env_var(char *input, t_elst *lst)
{
	static char	buffer[DATA_SIZE];
	char		env_name[MAX_KEY_VAR];
	char		*ptr;
	char		*bptr;

	ptr = input;
	bptr = buffer;
	while (*ptr)
	{
		if (*ptr == '$')
		{
			ptr++;
			ptr = extract_env_key(ptr, env_name);
			bptr = replace_with_env_value(bptr, env_name, lst);
		}
		else
			*bptr++ = *ptr++;
	}
	*bptr = '\0';
	return (buffer);
}

static void	child_heredoc(char *line, char *end_marker, int *fd, t_elst *lst)
{
	char	*expanded_line;

	close(fd[0]);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strequ(line, end_marker))
		{
			free(line);
			break ;
		}
		expanded_line = replace_env_var(line, lst);
		ft_putendl_fd(expanded_line, fd[1]);
		free(line);
	}
	close(fd[1]);
	exit(0);
}

// implement heredoc handling and execution
void	flag_heredoc(t_sent *node, t_elst *lst)
{
	char	*line;
	char	*end_marker;
	int		fd[2];
	pid_t	pid;

	line = NULL;
	end_marker = node->input_argv;
	pipe(fd);
	pid = fork();
	if (pid < 0)
		ft_error();
	if (pid == 0)
	{
		child_heredoc(line, end_marker, fd, lst);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
