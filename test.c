#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			fileout = open_file(argv[argc - 1], 0);
			heredoc(argv[2], argc);
			i = 3;
		}
		else
		{
			fileout = open_file(argv[argc - 1], 1);
			filein = open_file(argv[1], 2);
			dup2(filein, STDIN_FILENO);
			i = 2;
		}
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		ft_exec(argv[argc - 2], envp);
	}
	instruction();
}
