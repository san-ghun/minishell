#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	//test : ft_strtok
	char s[] = "This is the way.";
	char d[] = " ";

	char *portion1 = ft_strtok(s, d);
	printf("%s\n", portion1);
	portion1 = ft_strtok(NULL, d);
	printf("%s\n", portion1);
	portion1 = ft_strtok(NULL, d);
	printf("%s\n", portion1);
	portion1 = ft_strtok(NULL, d);
	printf("%s\n", portion1);
	portion1 = ft_strtok(NULL, d);
	printf("%s\n", portion1);

	return (0);
}
