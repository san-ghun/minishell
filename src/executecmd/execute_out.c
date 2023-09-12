/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 00:00:52 by minakim           #+#    #+#             */
/*   Updated: 2023/09/13 00:02:02 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: implement output pipe handling and execution
void	execute_pipe_output(t_sent *node, t_elst *lst)
{
	execute_node(node, lst);
}

// TODO: implement output redirection write append handling and execution
void	execute_redi_append(t_sent *node, t_elst *lst)
{
	execute_node(node, lst);
}

// TODO: implement output redirection write trunc handling and execution
void	execute_redi_trunc(t_sent *node, t_elst *lst)
{
	execute_node(node, lst);
}