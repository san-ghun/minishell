#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	//test : ft_strcspn
	char string[] = "here is test functions";
	char digit[] = " heristfn";

	size_t length = ft_strcspn(string, digit);
	printf("%d\n", (int)length);
	length = strcspn(string, digit);
	printf("%d\n", (int)length);
}
