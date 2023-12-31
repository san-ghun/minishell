/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:43:37 by minakim           #+#    #+#             */
/*   Updated: 2023/11/23 16:40:45 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redi_out(t_sent *node)
{
	int	fd;

	fd = 1;
	if (node->output_flag == REDI_WR_APPEND_FLAG)
		fd = open_file(node->output_argv, 0);
	else if (node->output_flag == REDI_WR_TRUNC_FLAG)
		fd = open_file(node->output_argv, 1);
	else if (node->input_flag == HDOC_FLAG || node->input_flag == REDI_RD_FLAG)
		fd = -2;
	if (fd == -1)
		ms_error("redirection out: unable to read the file\n");
	return (fd);
}

static int	echo_flagcheck(const char *str)
{
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
/// This function examines the input string and checks for 
/// the presence of the "-n" flag. If the flag is found, 
/// it sets the 'i' parameter to 1, indicating that the 'echo' command
/// should start from the second token. If the flag is not present, 
/// 'i' is set to 0, indicating that the 'echo' command should start 
/// from the first token.
/// @param[in]  str  The input string to analyze for the "-n" flag.
/// @param[out] i    A pointer to an integer that will hold 
/// the index for token processing.
/// @return The termination character ('%' or '\\n') based on 
/// the presence of the "-n" flag.
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

void	ft_echo(t_sent *node, t_elst *lst)
{
	int		i;
	char	term;
	int		fd;

	i = 0;
	fd = redi_out(node);
	if (fd == -2)
		return ;
	if (node->tokens[1])
	{
		term = determine_term(node->tokens[1], &i);
		while (++i < node->tokens_len && node->tokens[i])
		{
			ft_putstr_fd(node->tokens[i], fd);
			if (i + 1 < node->tokens_len && node->tokens[i + 1] != NULL)
				ft_putchar_fd(' ', fd);
		}
		ft_putchar_fd(term, fd);
	}
	else
		ft_putendl_fd("", fd);
	if (fd != 1)
		close(fd);
	lst->g_exit = 0;
}
