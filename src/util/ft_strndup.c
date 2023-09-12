/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:13:26 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/13 00:09:11 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/// @brief Duplicates a substring from `src` up to `len` characters.
/// If a pointer is passed, `src` starts from the position of the pointer.
/// @param src The source string.
/// @param len The length of characters to copy.
/// @return A newly allocated substring, or NULL on allocation failure.
char	*ft_strndup(const char *src, size_t len)
{
	char	*new;

	new = (char *)ft_memalloc(len + 1);
	if (!new)
		return (NULL);
	return (ft_strncpy(new, src, len));
}
