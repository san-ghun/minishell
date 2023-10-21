/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:25:28 by sanghupa          #+#    #+#             */
/*   Updated: 2023/10/14 17:20:11 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ms_split_size(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if (*s != c)
		{
			len++;
			while (*s && *s != c)
				s++;
		}
		if (*s)
			s++;
	}
	return (len);
}

char	**ms_split_process(char const *s, char c, char **tmp, size_t i)
{
	char	*start;

	while (*s)
	{
		if (*s != c)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			tmp[i] = (char *)malloc(sizeof(char) * (s - start + 1));
			if (!tmp[i])
				return (NULL);
			ft_strlcpy(tmp[i++], start, s - start + 1);
		}
		if (*s)
			s++;
	}
	tmp[i] = NULL;
	return (tmp);
}

char	**ms_split(char const *s, char c)
{
	char	**tmp;
	size_t	i;

	if (!s)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * (ms_split_size(s, c) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	tmp = ms_split_process(s, c, tmp, i);
	return (tmp);
}
