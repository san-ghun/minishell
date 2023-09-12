/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:01:20 by sanghupa          #+#    #+#             */
/*   Updated: 2023/09/12 22:38:21 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// built-in functions check
typedef struct s_cmd
{
	char	*cmd_name;
	void	(*cmd_func)(t_sent *node, t_elst *lst);
}				t_cmd;

static int	dispatchcmd(t_sent *node, t_elst *lst)
{
	static t_cmd	cmd_table[] = {
	{"cd", ft_cd},
	{"echo", ft_echo},
	{"pwd", ft_pwd},
	{"env", ft_env},
	{NULL, NULL}
	};
	int				i;

	i = -1;
	while (cmd_table[++i].cmd_name)
	{
		if (ft_strequ(node->tokens[0], cmd_table[i].cmd_name))
		{
			cmd_table[i].cmd_func(node, lst);
			return (1);
		}
	}
	return (0);
}

/// TMP FUNCTION.
static void	free_menvp(char **menvp)
{
	int	i;

	i = -1;
	while (menvp[++i])
		free(menvp[i]);
	free(menvp);
	menvp = NULL;
}

void	execute_node(t_sent *node, t_elst *lst)
{
	pid_t	pid;
	char	**menvp;

	pid = fork();
	if (pid < 0)
	{
		perror("Error");
		ft_putstr_fd("Failed to fork\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (node->tokens[0] == NULL)
			exit(EXIT_SUCCESS);
		if (dispatchcmd(node, lst))
			exit(EXIT_SUCCESS);
		menvp = dll_to_envp(lst);
		ft_exec(node->tokens, menvp);
		free_menvp(menvp);
		perror("Error");
		ft_putstr_fd("Failed to execute command\n", 2);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
}

void	executecmd(t_deque *deque, t_elst *lst)
{
	int		filein;
	int		fileout;
	t_sent	*node;

	while (0 < deque->size)
	{
		node = deque_pop_back(deque);
		// TODO: implement execution stage
		if (node->input_flag == HDOC_FLAG)
		{
			// handle input heredoc 
			execute_node(node, lst);
		}
		else if (node->input_flag == REDI_RD_FLAG)
		{
			// handle input redirection read
			execute_node(node, lst);
		}
		else if (node->input_flag == PIPE_FLAG)
		{
			// handle input pipe
			execute_node(node, lst);
		}
		if (node->output_flag == PIPE_FLAG)
		{
			// handle output pipe
			execute_node(node, lst);
		}
		else if (node->output_flag == REDI_WR_APPEND_FLAG)
		{
			// handle output redirection write append
			execute_node(node, lst);
		}
		else if (node->output_flag == REDI_WR_TRUNC_FLAG)
		{
			// handle output redirection write trunc
			execute_node(node, lst);
		}
		else
			execute_node(node, lst);
	}
	return ;
}
