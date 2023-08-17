/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:19:20 by minakim           #+#    #+#             */
/*   Updated: 2023/08/08 13:33:26 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

/**
 * @brief Duplicates a substring from `src` up to the first occurrence of `c`.
 * If a pointer is passed, `src` starts from the position of the pointer.
 * @param src The source string.
 * @param c The delimiter character.
 * @return A newly allocated substring, or NULL on allocation failure.
 */
char	*ft_strcdup(const char *src, char c)
{
	char	*new;
	int		len;
	int		i;

	len = 0;
	while (src[len] != c && src[len])
		len++;
	new = (char *) ft_memalloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = src[i];
		i++;
	}
	return (new);
}
