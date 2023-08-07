/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:59:27 by minakim           #+#    #+#             */
/*   Updated: 2023/07/24 22:08:09 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtok(char *str, const char *delim);

// This function Depends on ft_strtok.
// static void	set_token_ptr(char *str, char **start_ptr, char **tok_ptr)
// {
// 	if (str != NULL)
// 	{
// 		*start_ptr = str;
// 		*tok_ptr = str;
// 	}
// 	else
// 		*start_ptr = *tok_ptr;
// }

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
// - Make tokenizing able to span multiple spaces or multiple characters.
char	*ft_strtok(char *str, const char *delim)
{
	static char	*olds;
	char		*token;

	if (str == NULL)
		str = olds;
	str += ft_strspn(str, delim);
	if (*str == '\0')
	{
		olds = str;
		return (NULL);
	}
	token = str;
	str = ft_strpbrk(token, delim);
	if (str == NULL)
		olds = "";
	else
	{
		*str = '\0';
		olds = str + 1;
	}
	return (token);
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
