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