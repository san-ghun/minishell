/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:05:52 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/23 16:19:56 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strspn(const char *str, const char *delim);

/// @brief Calculates the length of the initial segment of a string 
/// that consists entirely of characters from a specified set.
/// @param str  The string to be examined.
/// @param delim The set of characters to be used as delimiters.
/// @return The length of the initial segment of 'str'
/// that matches any character in 'delim'.
size_t	ft_strspn(const char *str, const char *delim)
{
	size_t	initial_length;
	int		found_match;
	size_t	i;
	size_t	j;

	initial_length = 0;
	i = -1;
	while (++i < ft_strlen(str))
	{
		found_match = 0;
		j = -1;
		while (++j < ft_strlen(delim))
		{
			if (delim[j] == str[i])
			{
				found_match = 1;
				break ;
			}
		}
		if (!found_match)
			break ;
		else
			initial_length++;
	}
	return (initial_length);
}
//#include <stdio.h>
//int main(void)
//{
//	//test : ft_strspn
//	char string[] = "here is test functions";
//	char digit[] = " ";
//
//	size_t length = ft_strspn(string, digit);
//	printf("%zu\n", length);
//	length = strspn(string, digit);
//	printf("%zu\n", length);
//}
