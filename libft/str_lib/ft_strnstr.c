/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:44:43 by sanghupa          #+#    #+#             */
/*   Updated: 2022/12/29 22:40:09 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_hs;
	size_t	len_nd;
	size_t	len_tmp;
	size_t	i;

	if (needle[0] == '\0')
		return ((char *)haystack);
	len_hs = ft_strlen(haystack);
	len_nd = ft_strlen(needle);
	if (len_hs < len_nd || len < len_nd)
		return (0);
	if (len_hs > len)
		len_tmp = len;
	else
		len_tmp = len_hs;
	i = 0;
	while (i + len_nd <= len_tmp)
	{
		if (ft_strncmp(haystack + i, needle, len_nd) == 0)
			return ((char *)haystack + i);
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
	size_t	n;
	char	*res_org;
	char	*res_ft;

	strcpy(str1, "This is an example.");
	strcpy(str2, "This");
	// n = 1;
	n = 4;

	res_org = strnstr(str1, str2, n);
	res_ft = ft_strnstr(str1, str2, n);
	printf("str1 is |%s| \n", str1);
	printf("str2 is |%s| \n", str2);
	printf("src: result is - |%s|\n", res_org);
	printf("ft_: result is - |%s|\n\n", res_ft);
	return (0);
}
*/
