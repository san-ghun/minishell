/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:06:52 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/23 16:20:19 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strpbrk(const char *str, const char *delim);

/// @brief Searches a string for any character from a specified set.
/// And returns a pointer to the first occurrence of the character.
/// @param str The string to be searched.
/// @param delim The set of characters to search for.
/// @return A pointer to the first occurrence of any character from
/// 'delim' in 'str', or NULL if no match is found.
char	*ft_strpbrk(const char *str, const char *delim)
{
	const char	*a;

	while (*str != '\0')
	{
		a = delim;
		while (*a != '\0')
		{
			if (*str == *a)
				return ((char *)str);
			a++;
		}
		++str;
	}
	return (NULL);
}
