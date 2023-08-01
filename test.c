/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:15:06 by minakim           #+#    #+#             */
/*   Updated: 2023/08/01 14:21:41 by minakim          ###   ########.fr       */
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
	if (!cmds)
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
/// 받아 "를 trim한 뒤 유효한 문자열 만큼 malloc하고 복사하여 return 합니다.
/// 1. while 루프를 이용해 문자열의 (큰따옴표 의)앞, 뒤 공백을 제거하거나 큰따옴표를 제거하는 과정에서,
/// 문자열의 모든 문자가 제거되어 '실질적인' 길이(end)가 0이 될 때
/// 2. trim_quote 함수에서 문자열의 첫 번째 문자 이후에 공백이나 큰따옴표가 없을 때,
/// 즉 문자열의 길이(len)와 현재 처리하려는 위치(start)가 같거나 start가 더 클 때
/// null 문자(\0)만 저장된 문자열이 반환됩니다!
/// 문자열 처리 함수들이 제대로 동작하고, 문자열이 아무 문자도 포함하지 않는다는 것을 명확하게 하기 위해서 입니다.
/// 닫히지 않은 큰따옴표는 그대로 복사됩니다.
static char *trim_util(char *str, size_t start, size_t end)
{
	if (end - start >= 0)
	{
		str = (char*)ft_memalloc(end - start + 1);
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

size_t skip_whitespace_and_quote_from_start(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '"')
		i++;
	return (i);
}

size_t skip_whitespace_and_quote_from_end(char *str, size_t len)
{
	while (len > 0 && ft_isspace(str[len]))
		len--;
	if (len > 0 && str[len] == '"')
		len--;
	return (len);
}


static char	*trim_quote(char *str)
{
	char	*new;
	size_t	start;
	size_t	i;
	size_t	end;

	if (!str)
		return (NULL);
	end = ft_strlen(str);
	start = skip_whitespace_and_quote_from_start(str);
	end = skip_whitespace_and_quote_from_end(str, end);
	new = trim_util(str, start, end);
	if (!new)
		return (NULL);
	i = -1;
	while (++i < end - start)
		new[i] = str[start + i];
	new[i] = '\0';
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


char	*ft_strndup(const char *src, size_t len)
{
	char	*str;

	str = (char *)ft_memalloc(len + 1);
	if (!str)
		return (NULL);
	return (ft_strncpy(str, src, len));
}

char		**tokenise(char *cmd, int size)
{
	int		i;
	int		j;
	int		len;
	char	**token;

	token = (char **)ft_memalloc(sizeof(char*) * (size + 1));
	if (!token)
	{
		ft_printf("???\n");
		return (NULL);
	}
	i = -1;
	j = 0;
	while (++i < size)
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
		ft_printf("token [%s]\n", token[i]);
		j += len;
		/// 토큰화 된 결과가 ["             here    ] 처럼 큰 따옴표로 시작된다면
		/// 다음 parse 과정에서 유효하지 않게 해야합니다.
		/// 테스팅이 필요한 부분, "1234""4567" , "1234'1'5678"
		/// [1234""4567] [1234'1'5678] 처럼 토큰화 된다면 다음 perse 과정에서
		/// 알맞은 형태로 한번 더 parse 해야 합니다!
	}
	return (token);
}

void	init_lst(char **cmds, t_deque **lst)
{
	int i;
	t_sent *node;

	if (cmds == NULL)
		return ;
	i = -1;
	/// 이후 수정 필수. 현재는 테스트 형식.
	node = ft_memalloc(sizeof (t_sent));
	node->prev = NULL;
	while (++i < (*lst)->size && node != NULL)
	{
		node->token = tokenise(cmds[i], (*lst)->size);
		node = node->prev;
	}
}

void *print_all_test(t_deque *lst)
{
	t_sent *node;
	int	i;
	i = -1;
	node = lst->begin;
	while(node != NULL)
	{
		while (node->token[i] != NULL)
			ft_printf("%s\n", node->token[i]);
		node = node->next;
	}
}

size_t	readcmd(char *cmd)
{
	size_t	len;
	size_t	total_len;
	char	temp_cmd[MAX_COMMAND_LEN];

	total_len = 0;
	ft_strlcpy(cmd, "", 2);
	if (*cmd != '\0')
		exit(EXIT_FAILURE);
	total_len = ft_strlen(cmd);
	while (1)
	{
		getcmd(temp_cmd, 0);
		len = ft_strcspn(temp_cmd, "\n");
		if (len == 0 || temp_cmd[len - 1] != '\\')
		{
			ft_strlcat(cmd, temp_cmd, ft_strlen(cmd) + len + 1);
			break ;
		}
		ft_strlcat(cmd, temp_cmd, ft_strlen(cmd) + len);
	}
	total_len = ft_strlen(cmd);
	cmd[total_len] = '\0';
	return (total_len);
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


int	main(int ac, char **av)
{
	t_deque *lst;
	char	cmd[MAX_COMMAND_LEN];

	readcmd(cmd);
	lst = ft_memalloc(sizeof(t_deque));

	parsecmd(cmd, &lst);

	print_all_test(lst);
}