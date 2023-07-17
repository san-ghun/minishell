/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:19:20 by sanghupa          #+#    #+#             */
/*   Updated: 2022/12/30 02:17:42 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

/// @brief produce output according to a `format`, 
/// and write output to stdout, the standard output stream.
/// The function write the output under the control of a `format` string.
/// @param format string that specifies 
/// how subsequent arguments are converted for output.
/// @param ... subsequent arguments or arguments accessed via 
/// the variable-length argument facilities of stdarg(3).
/// @return the number of characters printed. 
/// (not including the trailing '\0' used to end ouput to strings)
int		ft_printf(const char *format, ...);

/// @brief print a single character
/// @param c the character to print
/// @return the number of characters printed
int		ft_put_c(int c);

/// @brief print a string (as defined by the common C conversion)
/// @param s the string to print
/// @return the number of characters printed
int		ft_put_s(char *s);

/// @brief print a pointer, 
/// the `void *` pointer argument has to be printed in hexadecimal format.
/// @param p the pointer to print
/// @return the number of characters printed
int		ft_put_p(unsigned long long p);

/// @brief print an (signed / unsigned) integer decimal (base 10) number
/// @param i the integer to print
/// @return the number of characters printed
int		ft_put_diu(long long i);

/// @brief print a number in hexadecimal (base 16)
/// @param x the hexadecimal number to print
/// @param uppercase indicate to print the number in uppercase format or not.
/// @return the number of characters printed
int		ft_put_hex(long long x, int uppercase);

#endif
