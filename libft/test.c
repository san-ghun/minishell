/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:56:07 by minakim           #+#    #+#             */
/*   Updated: 2023/10/03 17:24:21 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

int	main(void)
{
	int		temp;
	char	*ret;

    temp = 112;
	ft_printf("Value ft_printf() as deciaml, %d\n", temp);
    ft_printf("Value ft_printf() as char, %c\n", temp);
	
	ret = get_next_line(-1);
	ft_printf("Testing gnl and result is, %s\n", ret);
    return (0);
}
