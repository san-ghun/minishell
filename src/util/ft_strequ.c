/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strqu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:10:17 by minakim           #+#    #+#             */
/*   Updated: 2023/08/08 13:31:46 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// This was created by borrowing from other code due to a notation issue.
/// @return This function returns 1 if the strings being compared are equal
/// and 0 if they are not.
int	ft_strequ(char const *s1, char const *s2)
{
	if (s1 && s2 && ft_strcmp(s1, s2) == 0)
		return (1);
	return (0);
}
