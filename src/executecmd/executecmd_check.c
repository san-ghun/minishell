/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:38:30 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/21 16:38:51 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(char *path)
{
	if (path == NULL)
		return (ms_error("check_path error\n"));
	return (0);
}

int	check_pid(pid_t pid)
{
	if (pid < 0)
		return (ms_error("unable to fork\n"));
	return (0);
}
