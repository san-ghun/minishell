/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:00:38 by sanghupa          #+#    #+#             */
/*   Updated: 2023/06/19 00:45:38 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define INT_MAX_STR "2147483647"
# define INT_MIN_STR "-2147483648"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* is_ functions */

/// @brief decimal-digit character test
/// @param c the character to test
/// @return non-zero value if c is a digit, zero otherwise.
int		ft_isdigit(int c);

/// @brief alphabetic character test
/// @param c the character to test
/// @return non-zero value if c is an alphabet, zero otherwise.
int		ft_isalpha(int c);

/// @brief alphanumeric character test
/// @param c the character to test
/// @return non-zero value if c is a digit or a letter, zero otherwise.
int		ft_isalnum(int c);

/// @brief test for ASCII character
/// @param c the character to test
/// @return non-zero value if c is an ASCII character, zero otherwise.
int		ft_isascii(int c);

/// @brief printing character test (space character inclusive)
/// @param c the character to test
/// @return non-zero value if c is a printable, zero otherwise.
int		ft_isprint(int c);

/* to_ functions */

/// @brief lower case to upper case letter conversion
/// @param c the letter to be converted to upper case
/// @return upper case letter equivalent to `c`, else `c` remains unchanged.
int		ft_toupper(int c);

/// @brief upper case to lower case letter conversion
/// @param c the letter to be converted to lower case
/// @return lower case letter equivalent to `c`, else `c` remains unchanged.
int		ft_tolower(int c);

/* string (lib) functions */

/// @brief compute the length of the string, 
/// but not including the terminating null character
/// @param s the string whose length is to be found.
/// @return the length of the string.
size_t	ft_strlen(const char *s);

/// @brief copy up to `dstsize` characters from the string pointed to, 
/// by src to dst. In a case where the length of src is less than 
/// that of dstsize, the remainder of dst will be padded with null bytes.
/// @param dst pointer to the dest array where the content is to be pasted.
/// @param src the string to be copied.
/// @param dstsize The number of characters to be copied from source.
/// @return the pointer to the pasted string.
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/// @brief append the string pointed to by `src` to the end of the string 
/// pointed to by `dst` up to `dstsize` characters long.
/// @param dst pointer to the destination array, which should contain 
/// a C string, and should be large enough to contain the concatenated 
/// resulting string which includes the additional null-character.
/// @param src the string to be appended.
/// @param dstsize the maximum number of characters to be appended.
/// @return a pointer to the resulting string dst.
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/// @brief search for the first occurrence of the character `c` 
/// in the string pointed to by the argument `s`.
/// @param s the C string to be scanned.
/// @param c the character to be searched in `s`.
/// @return a pointer to the first occurrence of the character, 
/// or NULL if no such occurrence
char	*ft_strchr(const char *s, int c);

/// @brief search for the last occurrence of the character `c` 
/// in the string pointed to, by the argument `s`.
/// @param s the C string.
/// @param c the character to search
/// @return a pointer to the last occurrence of the character in `s`.
/// If no such character is found, NULL is returned.
char	*ft_strrchr(const char *s, int c);

/// @brief compare at most the first `n` bytes of `s1` and `s2`.
/// @param s1 the first string to compare
/// @param s2 the second string to compare
/// @param n the maximum number of characters to be compared.
/// @return rv > 0 : s1 > s2, rv < 0 : s1 < s2, rv == 0 : s1 == s2
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/// @brief finds the first occurrence of the substring `needle` 
/// in the string `haystack`, where not more than `len`. 
/// The terminating '\0' characters are not compared.
/// @param haystack the main C string to be scanned.
/// @param needle the small string to be searched with-in haystack.
/// @param len the maximum number of characters to search.
/// @return a pointer to the first occurrence of `needle` 
/// in the string `haystack`. If `needle` is empty, `haystack` is returned;
/// if `needle` is not occurs in `haystack`, NULL is returned.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/// @brief convert ASCII string to integer
/// @param str the string representation of an integral number
/// @return the converted inegral number as an int value. 
/// 		If no valid conversion could be performed, return zero.
int		ft_atoi(const char *str);

/// @brief duplicate string
/// @param s1 pointer to the null-terminated byte string to duplicate.
/// @return a pointer to the newly allocated string, 
/// or a NULL pointer if an error occurred.
char	*ft_strdup(const char *s1);

/* string (non-lib) functions */

/// @brief allocate with malloc() and returns a substring from `s`.
/// The substring begins at index `start` and is of maximum size `len`.
/// @param s The string from which to create the substring.
/// @param start The start index of the substring in the string ’s’.
/// @param len The maximum length of the substring.
/// @return The substring. NULL if the allocation fails.
char	*ft_substr(char const *s, unsigned int start, size_t len);

/// @brief allocate with malloc() and returns a new string, 
/// which is the result of the concatenation of `s1` and `s2`.
/// @param s1 the prefix string to concatenate
/// @param s2 the suffix string to concatenate
/// @return the new string. NULL if the allocation fails.
char	*ft_strjoin(char const *s1, char const *s2);

/// @brief allocate with malloc() and returns a copy of `s1` 
/// with the characters specified in `set` removed from 
/// the beginning and the end of the string.
/// @param s1 the string to be trimmed.
/// @param set the reference set of characters to trim.
/// @return the trimmed string. NULL if the allocation fails.
char	*ft_strtrim(char const *s1, char const *set);

/// @brief allocate with malloc() and returns a string representing 
/// the integer received as a argument. Negative numbers must be handled.
/// @param n the integer to convert.
/// @return the string representing the integer. NULL if the allocation fails.
char	*ft_itoa(int n);

/// @brief apply the function `f` to each character of the string `s`, 
/// and passing its index as first argument to create a new string 
/// with malloc() resulting from successive applicatioins of `f`.
/// @param s the string on which to iterate.
/// @param f the function to apply to each character.
/// @return the string created from the successive application of `f`. 
/// Returns NULL if the allocation fails.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/// @brief apply the function `f` on each character of the string 
/// passed as argument, passing its index as first argument. 
/// Each character is passed by address to `f` to be modified if necessary.
/// @param s the string on which to iterate.
/// @param f the function to apply to each character.
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/// @brief get the number of split strings obtained by splitting `s` 
/// using the character `c` as a delimiter in the string passed as an argument.
/// @param s the string to be split.
/// @param c the delimiter character.
/// @return the number of splited string.
size_t	ft_split_size(char const *s, char c);

/// @brief allocate with malloc() and returns an array of strings 
/// obtained by splitting `s` using the character `c` as a delimiter. 
/// The array must end with a NULL pointer.
/// @param s the string to be split.
/// @param c the delimiter character.
/// @return the array of new strings resulting from the split. 
/// NULL if the allocation fails.
char	**ft_split(char const *s, char c);

/* memory functions */

/// @brief copy the character `c` to the first `n` characters of 
/// the string pointed to, by the argument `str`.
/// @param b a pointer to the block of memory to fill.
/// @param c the value to be set.
/// @param len the number of bytes to be set to the value.
/// @return a pointer to the memory area `b`.
void	*ft_memset(void *b, int c, size_t len);

/// @brief write zeros to a byte string
/// @param s a byte string
/// @param n size of zeros to write
void	ft_bzero(void *s, size_t n);

/// @brief copy `n` characters from memory area `src` to memory area `dst`.
/// @param dst pointer to destination memory area where content is to be pasted.
/// @param src pointer to the source of data to be copied.
/// @param n the number of bytes to be copied.
/// @return a pointer to destination, which is `dst`.
void	*ft_memcpy(void *dst, const void *src, size_t n);

/// @brief copy `len` characters from `src` to `dst`, 
/// but for overlapping memory blocks, 
/// memmove() is a safer approach than memcpy().
/// @param dst pointer to destination memory area where content is to be pasted.
/// @param src pointer to the source of data to be copied.
/// @param len the number of bytes to be copied.
/// @return a pointer to the destination, which is `dst`.
void	*ft_memmove(void *dst, const void *src, size_t len);

/// @brief search for the first occurrence of the character 
/// `c` (converted to an unsigned char) in the first `n` bytes 
/// of the string pointed to, by the argument `s`.
/// @param s the pointer to the block of memory where the search in performed.
/// @param c the value to search for, by a byte per byte.
/// @param n the number of bytes to be analyzed.
/// @return a pointer to the matching byte or NULL if no match was found.
void	*ft_memchr(const void *s, int c, size_t n);

/// @brief compare the first `n` bytes of memory area `s1` and memory are `s2`.
/// @param s1 the pointer to a block of memory.
/// @param s2 the pointer to a block of memory.
/// @param n the number of bytes to be compared.
/// @return rv > 0 : s1 > s2, rv < 0 : s1 < s2, rv == 0 : s1 == s2
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/// @brief allocates the requested memory and returns a pointer to it.
///	The difference from malloc is that calloc sets allocated memeory to zero.
/// @param count the number of elements to be allocated.
/// @param size the size of elements.
/// @return a pointer to the allocated memeory, or NULL if the request fails.
void	*ft_calloc(size_t count, size_t size);

/* put_fd functions */

/// @brief ouput the character `c` to the given file descriptor.
/// @param c the character to ouput.
/// @param fd the file descriptor on which to ouput the character.
void	ft_putchar_fd(char c, int fd);

/// @brief ouput the string `s` to the given file descriptor
/// @param s the string to ouput.
/// @param fd the file descriptor on which to write.
void	ft_putstr_fd(char *s, int fd);

/// @brief ouput the string `s` to the given file descriptor 
/// followed by a newline.
/// @param s the string to ouput.
/// @param fd the file descriptor on which to write.
void	ft_putendl_fd(char *s, int fd);

/// @brief output the integer `n` to the given file descriptor
/// @param n the integer to output.
/// @param fd the file descriptor on which to write.
void	ft_putnbr_fd(int n, int fd);

/* linked list functions - bonus */

/// @brief allocate with malloc() and returns a new node. 
/// The member variable `content` is initialized with 
/// the value of the parameter `content`. 
/// The variable `next` is intialized to NULL.
/// @param content the content to create the node with.
/// @return the new node.
t_list	*ft_lstnew(void *content);

/// @brief add the node `new` at the beginning of the list.
/// @param lst the address of a pointer to the first link of a list.
/// @param new the address of a pointer to the node to be added to the list.
void	ft_lstadd_front(t_list **lst, t_list *new);

/// @brief count the number of nodes in a list.
/// @param lst the beginning of the list.
/// @return the length of the list.
int		ft_lstsize(t_list *lst);

/// @brief return the last node of the list.
/// @param lst the beinning of the list.
/// @return last node of the list.
t_list	*ft_lstlast(t_list *lst);

/// @brief add the node `new` at the end of the list.
/// @param lst the address of a pointer to the first link of a list.
/// @param new the address of a pointer to the the node to be added to the list.
void	ft_lstadd_back(t_list **lst, t_list *new);

/// @brief take as a parameter a node and free the memory of 
/// the node's content using the function `del` 
/// given as a parameter and free the node.
/// The memory of `next` must not be freed.
/// @param lst the node to free.
/// @param del the address of the functioin used to delete the content.
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/// @brief delete and free the given node and every successor of that node,
/// using the function `del` and free(). 
/// Finally, the pointer to the list must be set to NULL.
/// @param lst the address of a pointer to a node.
/// @param del the address of the function 
/// used to delete the content of the node.
void	ft_lstclear(t_list **lst, void (*del)(void *));

/// @brief iterate the list `lst` and apply the function `f` 
/// on the content of ezch node.
/// @param lst the address of a pointer to a node.
/// @param f the address of the functioni used to iterate on the list.
void	ft_lstiter(t_list *lst, void (*f)(void *));

/// @brief iterate the list `lst` and apply the function `f` 
/// to the content of each node. Create a new list resulting 
/// of the successive applications of the function `f`.
/// The `del` function is used to delete the content of a node if needed.
/// @param lst the address of a pointer to a node.
/// @param f the address of the function used to iterate on the list.
/// @param del the address of a the function used to delete 
/// the content of a node if needed.
/// @return the new list. NULL if the allocatioin fails.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
