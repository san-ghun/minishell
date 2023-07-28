/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:41 by sanghupa          #+#    #+#             */
/*   Updated: 2023/07/28 16:42:18 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sent_update(t_sent *sent[], char *old, char *new);

void	sent_update(t_sent *sent[], char *old, char *new)
{
	t_sent	*tmp;

	tmp = sent_getone(sent, old);
	if (!tmp)
		return ;
	tmp->cmd = new;
}
