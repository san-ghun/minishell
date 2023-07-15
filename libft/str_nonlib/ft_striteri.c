/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:57:26 by sanghupa          #+#    #+#             */
/*   Updated: 2022/12/29 22:42:50 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
	s[i] = '\0';
	return ;
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Not working properly may have to find other way to test.
void	f(unsigned int i, char *c)
{
	c[i] += 1;
	return ;
}
int	main(int ac, char **av)
{
	char	*str1;

	// strcpy(str1, "abcdefghijklmnopqrstuvwxyz");
	str1 = &av[1][0];
	ft_striteri(str1, *f);
	printf("%s\n", str1);

	return (0);
}
*/
