# libft

### Summary

This **libft** is a C library of my own, during 42 cursus.

1. Objective
    - coding a C library to create my own library with highly useful standard functions.
    - the functions will be allowed to use in other projects.

2. List of functions
    - Mandatory functions
        - **is_** : [`ft_isdigit`](./isto/ft_isdigit.c) [`ft_isalpha`](./isto/ft_isalpha.c) [`ft_isalnum`](./isto/ft_isalnum.c) [`ft_isascii`](./isto/ft_isascii.c) [`ft_isprint`](./isto/ft_isprint.c) 
        - **to_** : [`ft_toupper`](./isto/ft_toupper.c) [`ft_tolower`](./isto/ft_tolower.c)
        - **string(lib)** : [`ft_strlen`](./str_lib/ft_strlen.c) [`ft_strlcpy`](./str_lib/ft_strlcpy.c) [`ft_strlcat`](./str_lib/ft_strlcat.c) [`ft_strchr`](./str_lib/ft_strchr.c) [`ft_strrchr`](./str_lib/ft_strrchr.c) [`ft_strncmp`](./str_lib/ft_strncmp.c) [`ft_strnstr`](./str_lib/ft_strnstr.c) [`ft_atoi`](./str_lib/ft_atoi.c) [`ft_strdup`](./str_lib/ft_strdup.c) 
        - **string(non-lib)** : [`ft_substr`](./str_nonlib/ft_substr.c) [`ft_strjoin`](./str_nonlib/ft_strjoin.c) [`ft_strtrim`](./str_nonlib/ft_strtrim.c) [`ft_itoa`](./str_nonlib/ft_itoa.c) [`ft_strmapi`](./str_nonlib/ft_strmapi.c) [`ft_striteri`](./str_nonlib/ft_striteri.c) [`ft_split`](./str_nonlib/ft_split.c) 
        - **memory** : [`ft_memset`](./mem/ft_memset.c) [`ft_bzero`](./mem/ft_bzero.c) [`ft_memcpy`](./mem/ft_memcpy.c) [`ft_memmove`](./mem/ft_memmove.c) [`ft_memchr`](./mem/ft_memchr.c) [`ft_memcmp`](./mem/ft_memcmp.c) [`ft_calloc`](./mem/ft_calloc.c) 
        - **put_ft** : [`ft_putchar_fd`](./put_fd/ft_putchar_fd.c) [`ft_putstr_fd`](./put_fd/ft_putstr_fd.c) [`ft_putendl_fd`](./put_fd/ft_putendl_fd.c) [`ft_putnbr_fd`](./put_fd/ft_putnbr_fd.c)

    - Bonus functions
        - **linked_list** : [`ft_lstnew`](./llst/ft_lstnew.c) [`ft_lstadd_front`](./llst/ft_lstadd_front.c) [`ft_lstsize`](./llst/ft_lstsize.c) [`ft_lstlast`](./llst/ft_lstlast.c) [`ft_lstadd_back`](./llst/ft_lstadd_back.c) [`ft_lstdelone`](./llst/ft_lstdelone.c) [`ft_lstclear`](./llst/ft_lstclear.c) [`ft_lstiter`](./llst/ft_lstiter.c) [`ft_lstmap`](./llst/ft_lstmap.c) 
    
    - get_next_line (gnl)
        - **read** : [`get_next_line.c`](./gnl/get_next_line.c)

    - continue...
