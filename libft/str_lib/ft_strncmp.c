/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:48:14 by sanghupa          #+#    #+#             */
/*   Updated: 2022/12/29 22:39:53 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n)
	{
		if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0')
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int	main(int ac, char **av)
{
	char	str1[50];
	char	str2[50];
	int		n;
	int		res_org;
	int		res_ft;

	strcpy(str1, "This is an example.");
	strcpy(str2, "THIS IS AN EXAMPLE.");
	n = 1;

	res_org = strncmp(str1, str2, n);
	res_ft = ft_strncmp(str1, str2, n);
	printf("str1 is |%s| \n", str1);
	printf("str2 is |%s| \n", str2);
	printf("src: result is - |%d|\n", res_org);
	printf("ft_: result is - |%d|\n\n", res_ft);
	return (0);
}
*/
