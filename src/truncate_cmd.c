/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truncate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:07:44 by minakim           #+#    #+#             */
/*   Updated: 2023/08/01 17:43:59 by minakim          ###   ########.fr       */
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

int is_closed(const char *cmd)
{
	int i;
	uint8_t	quotes;
	uint8_t	dquotes;

	quotes = 0;
	dquotes = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '"' && quotes == 0)
			dquotes ^= 1;
		else if (cmd[i] == '\'' && dquotes == 0 && cmd[i + 2] == '\'')
			i += 2;
		else if (cmd[i] == '\'')
			quotes ^= 1;
	}
	if (quotes != 0 || dquotes != 0)
		return (0);
	return (1);
}


/// echo "     " -> ["         "] v1
/// echo "     " -> [           ] v2  << 어떤게 더 편할까? [결정]
char		**tokenise(char *cmd, int size)
{
	int		i;
	int		j;
	int		len;
	char	**token;

	token = (char **)ft_memalloc(sizeof(char*) * (size + 1));
	if (!token)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < size)
	{
		/// j 시작 포인트 (공백 문자를 스킵하고, 공백 문자가 아닌 위치만큼 움직인 뒤,
		/// 이동한 수만큼 리턴합니다.
		j += skip_spaces(&cmd[j]);
		/// len 토큰화 할 범위.
		/// 큰 따옴표로 닫혀 있다면 큰 따옴표가 있는 범위 만큼 (다음 공백문자에서 멈추므로 정확히는 큰따옴표 다음 공백 문자까지)
		///	아니라면 이어지는 문자열 만큼의 범위를 리턴합니다.
		len = to_next(&cmd[j]);

		/// 먼저 쌍따옴표/따옴표 갯수 (짝수인지) 확인하기
		/// is_close();

		if (cmd[j] == '"' && cmd[j + len - 1] == '"')
			token[i] = ft_strndup(&cmd[j + 1], len - 2);
		else
			token[i] = ft_strndup(&cmd[j], len);
		ft_printf("token [%s]\n", token[i]);
		j += len;
		/// 토큰화 된 결과가 ["             here    ] 처럼 큰 따옴표로 시작된다면
		/// 다음 parse 과정에서 유효하지 않게 해야 합니다.
		/// 테스팅이 필요한 부분, "1234""4567" , "1234'1'5678"
		/// [1234""4567] [1234'1'5678] 처럼 토큰화 된다면 다음 pe기rse 과정에서
		/// 알맞은 형태로 한번 더 parse 합니다.
	}
	return (token);
}
/// 아래와 같은 경우 가정할 때는 아직 안됨.
/// $ echo ""here" "is"   "oh""
/// $ here is   oh

void	init_lst(char **cmds, t_deque **lst)
{
	int i;
	t_sent *node;

	if (cmds == NULL)
		return ;
	i = -1;

	/// 이후 수정 필수. 현재는 테스트 형식. deque 완성 후 변경.
	/// (*lst)->begin; begin이 하나씩 (아래로) 밀려나는 방식
	/// (*lst)->end; 에서 뽑아서 쓴다
	node = ft_memalloc(sizeof (t_sent));
	node->prev = NULL;

	/// node = (*lst)->end; 로 시작해야 함.
	while (++i < (*lst)->size && node != NULL)
	{
		/// 세미콜론으로 잘린 char **cmds가 하나씩 토큰화 됩니다.
		node->token = tokenise(cmds[i], (*lst)->size);
		node = node->prev;
	}
}

int parsecmd(char *cmd, t_deque **lst)
{
	int size;
	char **cmds;

	size = get_lst_size(cmd); // 세미콜론을 기준으로 나눠서 총 리스트의 사이즈를 결정 (1부터 시작)
	cmds = truncate_cmd(cmd, &size);
	(*lst)->size = size;
	init_lst(cmds, lst);
	return (0);
}

