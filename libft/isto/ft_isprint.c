/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:41:18 by sanghupa          #+#    #+#             */
/*   Updated: 2022/12/29 22:36:40 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int	main(int ac, char **av)
{
	printf("ft: %d\n", ft_isprint(av[1][0]));
	return (0);
}*/
