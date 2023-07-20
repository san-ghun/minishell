#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	//test : ft_strtok
	char s1[] = "This !is !the !way.";
	char d[] = " !";

	char *portion1 = ft_strtok(s1, d);
	ft_printf("--ft_strtok--\n");
	ft_printf("%s\n", portion1);
	portion1 = ft_strtok(NULL, d);
	ft_printf("%s\n", portion1);
	portion1 = ft_strtok(NULL, d);
	ft_printf("%s\n", portion1);
	portion1 = ft_strtok(NULL, d);
	ft_printf("%s\n", portion1);
	portion1 = ft_strtok(NULL, d);
	ft_printf("%s\n", portion1);

	char s2[] = "This !is !the !way.";
	char *portion2 = strtok(s2, d);
	ft_printf("\n--strtok--\n");
	ft_printf("%s\n", portion2);
	portion2 = strtok(NULL, d);
	ft_printf("%s\n", portion2);
	portion2 = strtok(NULL, d);
	ft_printf("%s\n", portion2);
	portion2 = strtok(NULL, d);
	ft_printf("%s\n", portion2);
	portion2 = strtok(NULL, d);
	ft_printf("%s\n", portion2);

	return (0);
}
