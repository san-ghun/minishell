/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:59:33 by minakim           #+#    #+#             */
/*   Updated: 2023/08/01 13:18:09 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_lst_size(const char *cmd)
{
	int		i;
	int		count;
	uint8_t	quotes;

	count = 1;
	quotes = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '"')
			quotes ^= 1;
		else if (cmd[i] == ';' && !quotes)
			count++;
	}
	return (count);
}

char	**truncate_cmd(char *cmd, const int *size)
{
	char	**cmds;

	int 	i;
	int 	j;

	cmds = (char **)ft_memalloc(sizeof (char *) * (*size + 1));
	(!cmds)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < *size)
	{
		j++;
		cmds[i] = ft_strcdup(&cmd[j], ';');
		while(cmd[j] && cmd[j] != ';')
			j++;
	}
	return (cmds);
}

//int is_closed(const char *cmd)
//{
//	int i;
//	uint8_t	quotes;
//	uint8_t	dquotes;
//
//	quotes = 0;
//	dquotes = 0;
//	i = -1;
//	while (cmd[++i])
//	{
//		if (cmd[i] == '"' && quotes == 0)
//			dquotes ^= 1;
//		else if (cmd[i] == '\'' && dquotes == 0 && cmd[i + 2] == '\'')
//			i += 2;
//		else if (cmd[i] == '\'')
//			quotes ^= 1;
//	}
//	if (quotes != 0 || dquotes != 0)
//		return (0);
//	return (1);
//}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

static int	skip_spaces(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isspace(str[i]))
			break ;
	return (i);
}


/// 큰따옴표(")가 있는 str(문자열)를 파라미터(이 함수로 넘어오기전 확인해야 함)를 인수로
/// 받아 "를 trim하여 malloc의 크기를 바꾼 뒤 return 합니다.
/// 1. trim_quote while 루프를 이용해 문자열의 (큰따옴표 의)앞, 뒤 공백을 제거하거나 큰따옴표를 제거하는 과정에서,
/// 문자열의 모든 문자가 제거되어 '실질적인' 길이(len)가 0이 될 때
/// 2. trim_quote 함수에서 문자열의 첫 번째 문자 이후에 공백이나 큰따옴표가 없을 때,
/// 즉 문자열의 길이(len)와 현재 처리하려는 위치(i)가 같거나 i가 더 클 때
/// null 문자(\0)만 저장된 문자열이 반환됩니다!
/// 닫히지 않은 큰따옴표는 이 과정에서 다시 한번 확인니다.
static char *trim_util(char *str, size_t len, size_t i)
{
	if (len - i >= 0)
	{
		str = (char*)ft_memalloc(len - i + 1);
		if (!str)
			return (NULL);
		return (str);
	}
	else
	{
		str = (char*)ft_memalloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
}

static char	*trim_quote(char *str)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '"')
		i++;
	while (ft_isspace(str[len]))
		len--;
	if (str[len] == '"')
		len--;
	new = trim_util(str, len, i);
	if (!new)
		return (NULL);
	j = -1;
	while (++j < len - i)
		new[j] = str[i + j];
	new[j] = '\0';
	return (new);
}


/// 주어진 문자열 str에서 다음 토큰이 시작하는 인덱스를 반환합니다.
/// 함수는 str의 첫 인덱스(혹은 포인터 시작 위치)부터 시작하여 공백 문자가 아닌 문자를 찾습니다.
/// 큰따옴표(")에 포함된 공백 문자는 무시합니다.
/// 큰따옴표가 없거나 짝수개 있을 때(닫혀 있을 때)만 공백 문자로 토큰을 구분합니다.
static int	to_next(char *str)
{
	int		i;
	uint8_t	quotes;

	i = -1;
	quotes = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			quotes ^= 1;
		if (!quotes && ft_isspace(str[i]))
			break ;
	}
	return (i);
}

char		**tokenise(char *cmd, int size)
{
	int		i;
	int		j;
	int		len;
	char	**token;

	token = (char**)ft_memalloc(sizeof(char*) * (size + 1))));
	i = 0;
	j = 0;
	while (i < size)
	{
		/// j 시작 포인트 (공백 문자를 스킵하고, 공백 문자가 아닌 위치만큼 움직인 뒤,
		/// 이동한 수만큼 리턴합니다.
		j += skip_spaces(&cmd[j]);
		/// len 토큰화 할 범위.
		/// 큰 따옴표로 닫혀 있다면 큰 따옴표가 있는 범위 만큼(다음 공백문자에서 멈추므로 정확히는 큰따옴표 다음 공백 문자까지)
		///	아니라면 이어지는 문자열 만큼의 범위를 리턴합니다.
		len = to_next(&cmd[j]);
		if (cmd[j] == '"' && cmd[j + len - 1] == '"')
			token[i] = ft_strndup(&cmd[j + 1], len - 2);
		else
			token[i] = ft_strndup(&cmd[j], len);
		j += len;
		i++;
		/// 테스팅이 필요한 부분, "1234""4567" , "1234'1'5678"
		/// [1234""4567] [1234'1'5678] 처럼 토큰화 된다면 한번 더 파싱하면 되지 않을까 생각하는 중.
	}
	return (token);
}

void	init_lst(char **cmds, t_deque **lst)
{
	int i;
	t_sent *node;

	if (cmds == NULL)
		return (0);
	i = -1;
	node = (*lst)->end;
	while (++i < (*lst)->size && node != NULL)
	{
		node->token = tokenise(cmds[i], (*lst)->size);
		node = node->prev;
	}
}

int parsecmd(char *cmd, t_deque **lst)
{
	int size;
	char **cmds;

	size = get_lst_size(cmd);
	cmds = truncate_cmd(cmd, &size);
	(*lst)->size = size;
	init_lst(cmds, lst);
	return (0);
}
