/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatchcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:55:21 by minakim           #+#    #+#             */
/*   Updated: 2023/09/10 15:09:18 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

//typedef struct s_cmd
//{
//	char	*cmd_name;
//	int		(*cmd_func)(t_sent *node, t_elst *lst);
//}				t_cmd;
//
//static int	dispatchcmd(t_sent *node, t_elst *lst)
//{
//	static t_cmd	cmd_table[] = {
//	{"cd", ft_cd},
//	{"echo", ft_echo},
//	{"pwd", ft_pwd},
//	{"env", ft_env},
//	{NULL, NULL}};
//	int				i;
//
//	i = -1;
//	while (cmd_table[++i].cmd_name)
//	{
//		if (ft_strequ(node->tokens[0], cmd_table[i].cmd_name))
//		{
//			cmd_table[i].cmd_func(node, lst);
//			return (1);
//		}
//		i++;
//	}
//	return (0);
//}
