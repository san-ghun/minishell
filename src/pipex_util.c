/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:35:50 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/17 12:44:04 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief Look for the path link inside the environment variables, 
/// split and test each command path and return the right path.
/// @param cmd command that will be tested for the path
/// @param envp pointer to the environment variables
char	*find_path(char *cmd, char *envp[])
{
	int		i;
	char	**paths;
	char	*ppath;
	char	*path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		ppath = ft_strjoin(paths[i], "/");
		path = ft_strjoin(ppath, cmd);
		free(ppath);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
	return (0);
}

void	ft_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

/// @brief Process the taken command, find the path for the command
/// and execute the command with the found path
/// @param arg argument that contains the command for the path
/// @param envp pointer to the environment variables
void	ft_exec(char *arg[], char *envp[])
{
	char	**cmd;
	char	*path;

	cmd = arg;
	path = find_path(cmd[0], envp);
	if (path == NULL)
		ft_error();
	if (execve(path, cmd, envp) == -1)
		ft_error();
}

void	instruction(void)
{
	ft_putstr_fd("Error: invalid arguments\n", 2);
	ft_putstr_fd("eg: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <file>\n", 1);
	exit(EXIT_SUCCESS);
}

int	get_line(char *line[])
{
	int		i;
	int		r;
	char	c;
	char	*buffer;

	i = 0;
	r = 0;
	c = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && (c != '\n') && (c != '\0'))
	{
		if ((c != '\n') && (c != '\0'))
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[i + 1] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}
