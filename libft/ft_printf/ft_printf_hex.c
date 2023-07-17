/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 22:17:41 by sanghupa          #+#    #+#             */
/*   Updated: 2022/12/30 23:08:14 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_hexlen(long long nbr)
{
	int	i;

	i = 1;
	while (nbr >= 16)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

int	ft_put_hex(long long x, int uppercase)
{
	int		len;
	char	*base;

	len = 0;
	base = "0123456789abcdef";
	if (uppercase)
		base = "0123456789ABCDEF";
	if (x < 0)
	{
		write(1, "-", 1);
		len++;
		x *= -1;
	}
	if (x > 15)
	{
		ft_put_hex(x / 16, uppercase);
		ft_put_hex(x % 16, uppercase);
	}
	else
		write(1, &base[x], 1);
	len += ft_get_hexlen(x);
	return (len);
}
