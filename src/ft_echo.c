/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:43:37 by minakim           #+#    #+#             */
/*   Updated: 2023/08/04 16:12:57 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../include/minishell.h"
#include "../libft/include/libft.h"

/// Accept the first argument as a command and
/// the second as an option if it exactly matches the option command(-n),
/// skipping whitespace.

///Test (bash)
//$ echo '-n'
//>
//
//$ echo              '-n'
//>
//
//$              echo "-n"
//>
//
//$ echo     1   "-n"
//> 1 -n


/// This function was created assuming it was properly parsed.
/// The first argument(node->tokens[0]) is the echo.
void	ft_echo(t_sent *node)
{
	int i;
	char terminating;

	if (node->tokens[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	i = ft_strequ(node->tokens[1], "-n");
	if (i == TRUE)
		terminating = '%';
	else
		terminating = '\n';
	while(node->tokens[++i] != NULL)
	{
		ft_putstr_fd(node->tokens[i], 1);
		if (node->tokens[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd(terminating, 1);
}