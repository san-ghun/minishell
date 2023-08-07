/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:29:43 by minakim           #+#    #+#             */
/*   Updated: 2023/07/31 22:47:38 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memalloc(size_t size)
{
	void	*temp;

	temp = (void *)malloc(size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, size);
	return (temp);
}
