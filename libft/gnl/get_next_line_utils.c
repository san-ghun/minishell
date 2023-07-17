/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 23:23:26 by sanghupa          #+#    #+#             */
/*   Updated: 2023/01/06 17:03:59 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == 0)
	{
		i = ft_strlen_gnl((char *)s);
		return (&s[i]);
	}
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup_gnl(char *s1)
{
	int		i;
	int		len;
	char	*dst;

	i = 0;
	len = ft_strlen_gnl(s1);
	dst = (char *)malloc(sizeof(char) * len + 1);
	if (dst == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (!s1)
		return (ft_strdup_gnl(s2));
	i = 0;
	j = 0;
	tmp = (char *)malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!tmp)
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tmp[i + j] = s2[j];
		j++;
	}
	tmp[i + j] = '\0';
	free(s1);
	return (tmp);
}
