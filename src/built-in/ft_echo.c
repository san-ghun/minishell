/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:43:37 by minakim           #+#    #+#             */
/*   Updated: 2023/09/06 16:35:30 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

static int echo_flagcheck(const char *str)
{
	char	*tmp;
	while (*str && ft_isspace(*str))
		str++;
	if (ft_strnequ(str, "-n", 2))
	{
		str += 2;
		while (*str && *str == 'n')
			str++;
	}
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

/// @brief Determines the termination character for the 'echo' command.
///
/// This function examines the input string and checks for the presence of the "-n" flag.
/// If the flag is found, it sets the 'i' parameter to 1, indicating that the 'echo' command
/// should start from the second token. If the flag is not present, 'i' is set to 0, indicating
/// that the 'echo' command should start from the first token.
///
/// @param[in]  str  The input string to analyze for the "-n" flag.
/// @param[out] i    A pointer to an integer that will hold the index for token processing.
/// @return The termination character ('%' or '\n') based on the presence of the "-n" flag.
char	determine_term(const char *str, int *i)
{
	char	term;

	*i = echo_flagcheck(str);
	if (*i == 1)
		term = '\0';
	else
		term = '\n';
	return (term);
}

///  Tilde expansion for the home directory (~)
void	*echo_homepath(t_elst *lst)
{
	char	*path;

	path = NULL;
	path = env_getvalue(lst, "HOME");
	if (path)
		ft_putstr_fd(path, 1);
	else
		ft_putstr_fd("~", 1);
}

int	determine_toklen(int tok_len, char term)
{
	if (term == '\n')
		return (tok_len);
	if (term == '\0')
		return (tok_len);
	return (0);
}

/**
 * TODO : rewrite
 * @brief Executes the 'echo' command with enhanced features.
 *
 * This function processes the 'echo' command, supporting advanced features:
 * 1. Tilde expansion for the home directory (~).
 * 2. Redirection (TODO: to be implemented).
 * 3. File descriptor control (TODO: to be implemented).
 * 4. Exit code testing (TODO: to be implemented).
 *
 * @param node  A structure containing the 'echo' command and its tokens.
 * @param lst   A linked list containing environmental variables.
 */
void	ft_echo(t_sent *node, t_elst *lst)
{
	int		i;
	char	term;
	int		fd;

	i = 0;
	fd = 1;
	if (node->tokens[1])
		term = determine_term(node->tokens[1], &i);
	while (++i <node->tokens_len && node->tokens[i])
	{
		if (ft_strequ(node->tokens[i], "~"))
			echo_homepath(lst);
		else
			ft_putstr_fd(node->tokens[i], fd);
		if (i + 1  < node->tokens_len && node->tokens[i + 1] != NULL)
			ft_putchar_fd(' ', fd);
	}
	ft_putchar_fd(term, fd);
	lst->g_exit = 0;
}
