/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 23:23:40 by sanghupa          #+#    #+#             */
/*   Updated: 2023/01/06 17:04:31 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

/* main */

/// @brief return a line read from a file descriptor `fd`.
/// @param fd the file descriptor to read from.
/// @return read line if correctly behave, 
/// or a NULL if there is nothing else to read, or an error occurred.
char	*get_next_line(int fd);

char	*ft_add_bufs(int fd, char *bufs);
char	*ft_get_line(char *bufs);
char	*ft_update_bufs(char *bufs);

/* utils */

/// @brief search for the first occurrence of the character `c` 
/// in the string pointed to by the argument `s`.
/// @param s the C string to be scanned.
/// @param c the character to be searched in `s`.
/// @return a pointer to the first occurrence of the character, 
/// or NULL if no such occurrence
char	*ft_strchr_gnl(char *s, int c);

char	*ft_strdup_gnl(char *s1);

/// @brief allocate with malloc() and returns a new string, 
/// which is the result of the concatenation of `s1` and `s2`.
/// @param s1 the prefix string to concatenate
/// @param s2 the suffix string to concatenate
/// @return the new string. NULL if the allocation fails.
char	*ft_strjoin_gnl(char *s1, char *s2);

/// @brief compute the length of the string, 
/// but not including the terminating null character
/// @param s the string whose length is to be found.
/// @return the length of the string.
size_t	ft_strlen_gnl(char *s);

#endif
