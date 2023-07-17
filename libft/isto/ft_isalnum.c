/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:40:21 by sanghupa          #+#    #+#             */
/*   Updated: 2022/12/29 22:34:20 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int	main(int ac, char **av)
{
	printf("ft: %d\n", ft_isalnum(av[1][0]));
	return (0);
}*/
