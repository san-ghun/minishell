/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:07:12 by sanghupa          #+#    #+#             */
/*   Updated: 2023/08/24 16:50:10 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sent	*sent_new(char *p_unit, int is_redir, int is_pipe);
void	sent_addfront(t_sent *sent[], t_sent *new);
void	sent_addback(t_sent *sent[], t_sent *new);

static int	get_tokens_len(char *cmd)
{
	int		i;
	char	p[2];
	char	*tmp;
	char	*token;

	i = 0;
	tmp = ft_strdup(cmd);
	ft_strlcpy(p, (tmp + ft_strcspn(tmp, "\'\" ")), 2);
	token = ft_strtok(tmp, p);
	while ((token != NULL) && (i < MAX_TOKENS))
	{
		i++;
		tmp += ft_strspn(tmp, "\'\" ");
		ft_strlcpy(p, (tmp + ft_strcspn(tmp, "\'\" ")), 2);
		token = ft_strtok(NULL, p);
	}
	// if (tmp != NULL)
	free(tmp);
	return (i);
}

static int	tokenize_intochunk(char *cmd, char *tokens[], int tokens_len)
{
	int		i;
	char	p[2];
	char	*token;

	i = 0;
	ft_strlcpy(p, (cmd + ft_strcspn(cmd, "\'\" ")), 2);
	token = ft_strtok(cmd, p);
	while ((i < tokens_len) && (token != NULL) && (i < MAX_TOKENS))
	{
		tokens[i++] = ft_strtrim(token, " ");
		cmd += ft_strspn(cmd, "\'\" ");
		ft_strlcpy(p, (cmd + ft_strcspn(cmd, "\'\" ")), 2);
		token = ft_strtok(NULL, p);
	}
	return (i);
}

static char	**tokenize_process(char *p_unit, int tokens_len)
{
	// char	tmp[MAX_COMMAND_LEN / 100];
	char	*tmp;
	char	**tokens;

	// ft_strlcpy(tmp, "", 2);
	// ft_strlcpy(tmp, p_unit, ft_strlen(p_unit) + 2);
	tmp = ft_strdup(p_unit);
	tokens = (char **)ft_memalloc(sizeof(char *) * tokens_len + 1);
	tokenize_intochunk(tmp, tokens, tokens_len);
	free(tmp);
	return (tokens);
}

t_sent	*sent_new(char *p_unit, int is_redir, int is_pipe)
{
	t_sent	*this;

	this = (t_sent *)malloc(sizeof(t_sent));
	if (!this)
		return (NULL);
	this->p_unit = ft_strdup(p_unit);
	this->tokens_len = get_tokens_len(p_unit);
	this->tokens = tokenize_process(p_unit, this->tokens_len);
	this->is_redir = is_redir;
	this->is_pipe = is_pipe;
	this->prev = NULL;
	this->next = NULL;
	return (this);
}
