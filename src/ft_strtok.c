/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:59:27 by minakim           #+#    #+#             */
/*   Updated: 2023/07/20 13:39:58 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../libft/include/libft.h"
#include "minishell.h"

/**
 * @note These functions have been tested.
 * The three functions below, "ft_strpbrk, ft_strspn, and ft_strtok" have
 * connectivity and can be used together.
 */
char	*ft_strpbrk(const char *str, const char *delim);
size_t	ft_strspn(const char *str, const char *delim);
char	*ft_strtok(char *str, const char *delim);

/**
 * @brief Calculates the length of the initial segment of a string that consists
 * entirely of characters from a specified set.
 * @param str  The string to be examined.
 * @param delim The set of characters to be used as delimiters.
 * @return The length of the initial segment of 'str'
 * that matches any character in 'delim'.
 */
size_t	ft_strspn(const char *str, const char *delim)
{
	size_t	initial_length;
	int		found_match;
	size_t	i;
	size_t	j;

	initial_length = 0;
	i = -1;
	while (++i < ft_strlen(str))
	{
		found_match = 0;
		j = -1;
		while (++j < ft_strlen(delim))
		{
			if (delim[j] == str[i])
			{
				found_match = 1;
				break ;
			}
		}
		if (!found_match)
			break ;
		else
			initial_length++;
	}
	return (initial_length);
}
//#include <stdio.h>
//int main(void)
//{
//	//test : ft_strspn
//	char string[] = "here is test functions";
//	char digit[] = " ";
//
//	size_t length = ft_strspn(string, digit);
//	printf("%zu\n", length);
//	length = strspn(string, digit);
//	printf("%zu\n", length);
//}

/**
 * @brief Searches a string for any character from a specified set.
 * And returns a pointer to the first occurrence of the character.
 * @param str The string to be searched.
 * @param delim The set of characters to search for.
 * @return A pointer to the first occurrence of any character from
 * 'delim' in 'str', or NULL if no match is found.
 */
char	*ft_strpbrk(const char *str, const char *delim)
{
	const char	*a;

	while (*str != '\0')
	{
		a = delim;
		while (*a != '\0')
		{
			if (*str == *a)
				return ((char *)str);
			a++;
		}
		++str;
	}
	return (NULL);
}

// This function Depends on ft_strtok.
void	set_token_ptr(char *str, char **start_ptr, char **tok_ptr)
{
	if (str != NULL)
	{
		*start_ptr = str;
		*tok_ptr = str;
	}
	else
		*start_ptr = *tok_ptr;
}

/**
 * @brief Breaks a string into a sequence of tokens.
 * This function returns a 'char *' and cuts tokens from
 * the string by converting delim to '\0'
 * @param str The string to be tokenized. If NULL,
 * the function continues tokenizing the previous string.
 * @param delim The set of delimiter characters used to separate tokens.
 * @return A pointer to the next token found in 'str',
 * or NULL if no more tokens are found.
 */
// TODO: ft_strtok()
// - Make tokenizing able to span multiple spaces or multiple characters.
char	*ft_strtok(char *str, const char *delim)
{
	// static char	*olds;
	// char		*token;

	// if (str == NULL)
	// 	str = olds;
	// str += ft_strspn(str, delim);
	// if (*str == '\0')
	// {
	// 	olds = str;
	// 	return (NULL);
	// }
	// token = str;
	// str = ft_strpbrk(token, delim);
	// if (str == NULL)
	// 	ft_strlcpy(olds, "", 2);
	// else
	// {
	// 	*str = '\0';
	// 	olds = str + 1;
	// }
	// return (token);

	static char	*start_ptr;
	static char	*tok_ptr;
	char		*next_delim;

	set_token_ptr(str, &start_ptr, &tok_ptr);
	if (start_ptr == NULL || *start_ptr == '\0')
		return (NULL);
	else if (delim == NULL || *delim == '\0')
		return (start_ptr);
	next_delim = ft_strpbrk(start_ptr, delim);
	if (next_delim != NULL)
	{
		*next_delim = '\0';
		tok_ptr = next_delim + 1;
	}
	else
		tok_ptr = NULL;
	ft_printf("hey");
	return (start_ptr);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	//test : ft_strtok
// 	char s1[] = "This !is !the !way.";
// 	char d[] = "!";

// 	char *portion1 = ft_strtok(s1, d);
// 	printf("ft_strtok\n");
// 	printf("%s\n", portion1);
// 	portion1 = ft_strtok(NULL, d);
// 	printf("%s\n", portion1);
// 	portion1 = ft_strtok(NULL, d);
// 	printf("%s\n", portion1);
// 	portion1 = ft_strtok(NULL, d);
// 	printf("%s\n", portion1);
// 	portion1 = ft_strtok(NULL, d);
// 	printf("%s\n", portion1);

// 	char s2[] = "This !is !the !way.";
// 	char *portion2 = strtok(s2, d);
// 	printf("\nstrtok\n");
// 	printf("%s\n", portion2);
// 	portion2 = strtok(NULL, d);
// 	printf("%s\n", portion2);
// 	portion2 = strtok(NULL, d);
// 	printf("%s\n", portion2);
// 	portion2 = strtok(NULL, d);
// 	printf("%s\n", portion2);
// 	portion2 = strtok(NULL, d);
// 	printf("%s\n", portion2);

// 	return (0);
// }
