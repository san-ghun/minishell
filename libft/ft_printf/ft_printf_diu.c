/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_diu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 22:17:41 by sanghupa          #+#    #+#             */
/*   Updated: 2022/12/30 02:02:05 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_nbrlen(long long nbr)
{
	int	i;

	i = 1;
	while (nbr >= 10)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int	ft_put_diu(long long i)
{
	int		len;
	char	*base;

	len = 0;
	if (i == -9223372036854775807)
	{
		write(1, "-9223372036854775807", 20);
		return (20);
	}
	base = "0123456789";
	if (i < 0)
	{
		write(1, "-", 1);
		len++;
		i *= -1;
	}
	if (i > 9)
	{
		ft_put_diu(i / 10);
		ft_put_diu(i % 10);
	}
	else
		write(1, &base[i], 1);
	len += ft_get_nbrlen(i);
	return (len);
}
