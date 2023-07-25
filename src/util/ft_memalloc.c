/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:29:43 by minakim           #+#    #+#             */
/*   Updated: 2023/07/24 22:04:33 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memalloc(size_t size)
{
	void	*temp;

	NULL_CHECK(!(temp = (void *)malloc(size)));
	ft_bzero(temp, size);
	return (temp);
}
