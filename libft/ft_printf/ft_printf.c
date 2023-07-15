/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:20:17 by sanghupa          #+#    #+#             */
/*   Updated: 2023/01/05 12:27:01 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert(va_list args, const char spec)
{
	unsigned long	ptr;

	if (spec == 'c')
		return (ft_put_c(va_arg(args, int)));
	else if (spec == 's')
		return (ft_put_s(va_arg(args, char *)));
	else if (spec == 'p')
	{
		ptr = va_arg(args, unsigned long long);
		if (!ptr)
			return (ft_put_s("(nil)"));
		write(1, "0x", 2);
		return (ft_put_p(ptr) + 2);
	}
	else if (spec == 'd' || spec == 'i')
		return (ft_put_diu(va_arg(args, int)));
	else if (spec == 'u')
		return (ft_put_diu(va_arg(args, unsigned int)));
	else if (spec == 'x' || spec == 'X')
		return (ft_put_hex(va_arg(args, unsigned int), 'x' - spec));
	else if (spec == '%')
		return (ft_put_c('%'));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	if (!format)
		return (0);
	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (ft_strchr("cspdiuxX%", format[i + 1]))
				len += ft_convert(args, format[++i]);
		}
		else
			len += ft_put_c(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}
