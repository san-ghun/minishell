/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:46:47 by sanghupa          #+#    #+#             */
/*   Updated: 2022/12/29 22:37:59 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int	main(int ac, char **av)
{
	char	str[50];
	int		len_src;
	int		len_ft;

	strcpy(str, "This is an example.");
	len_src = (int)strlen(str);
	len_ft = (int)ft_strlen(str);
	printf("Length of |%s| is: \n", str);
	printf("src: %d\n", len_src);
	printf("ft_: %d\n", len_ft);
	return (0);
}
*/
