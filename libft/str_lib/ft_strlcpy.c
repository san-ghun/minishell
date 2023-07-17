/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:52:47 by sanghupa          #+#    #+#             */
/*   Updated: 2022/12/29 22:38:22 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (len_src);
	while ((src[i] != '\0') && (i + 1 < dstsize))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	while (src[i] != 0)
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
	char	src[100];
	char	dst_org[100];
	char	dst_ft[100];

	strcpy(src, "This is an example.");
	strlcpy(dst_org, src, 15);
	ft_strlcpy(dst_ft, src, 15);
	printf("Copy 10 of |%s| is: \n", src);
	printf("src: %s\n", dst_org);
	printf("ft_: %s\n", dst_ft);
	return (0);
}
*/
