/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:41:35 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/15 15:44:06 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char *argv[], char *envp[])
{
	print_envp(envp);
	return (0);
}
