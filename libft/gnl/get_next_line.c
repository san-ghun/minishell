/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 23:22:56 by sanghupa          #+#    #+#             */
/*   Updated: 2023/01/06 17:03:52 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_update_bufs(char *bufs)
{
	size_t	i;
	size_t	j;
	char	*updated;

	i = 0;
	while (bufs[i] && bufs[i] != '\n')
		i++;
	if (bufs[i] == '\0')
	{
		free(bufs);
		return (NULL);
	}
	i += (bufs[i] == '\n');
	updated = (char *)malloc(sizeof(char) * (ft_strlen_gnl(bufs) - i + 1));
	if (!updated)
		return (NULL);
	j = 0;
	while (bufs[i + j])
	{
		updated[j] = bufs[i + j];
		j++;
	}
	updated[j] = '\0';
	free(bufs);
	return (updated);
}

char	*ft_get_line(char *bufs)
{
	size_t	i;
	char	*line;

	if (!bufs || (bufs[0] == '\0'))
		return (NULL);
	i = 0;
	while (bufs[i] && bufs[i] != '\n')
		i++;
	if (bufs[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (bufs[i] && bufs[i] != '\n')
	{
		line[i] = bufs[i];
		i++;
	}
	if (bufs[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_add_bufs(int fd, char *bufs)
{
	char	*buf;
	int		byte_read;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	byte_read = 1;
	while (!ft_strchr_gnl(bufs, '\n') && byte_read != 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buf);
			free(bufs);
			return (NULL);
		}
		buf[byte_read] = '\0';
		bufs = ft_strjoin_gnl(bufs, buf);
	}
	free(buf);
	return (bufs);
}

char	*get_next_line(int fd)
{
	static char	*bufs[512];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 511)
		return (NULL);
	bufs[fd] = ft_add_bufs(fd, bufs[fd]);
	if (!bufs[fd])
		return (NULL);
	line = ft_get_line(bufs[fd]);
	bufs[fd] = ft_update_bufs(bufs[fd]);
	return (line);
}

/* ----- TEST ----- */
// #include <fcntl.h>
// #include <stdio.h>
// #include <string.h>
// char	*get_next_line_DEBUG(int fd)
// {
// 	static char	*bufs[512];
// 	char		*line;

// 	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 511)
// 		return (NULL);
// 	// printf("bufs init: %s(BUF_END)\n", bufs[fd]);
// 	bufs[fd] = ft_add_bufs(fd, bufs[fd]);
// 	if (!bufs[fd])
// 		return (NULL);
// 	// printf("bufs before read: %s(BUF_END)\n", bufs[fd]);
// 	line = ft_get_line(bufs[fd]);
// 	bufs[fd] = ft_update_bufs(bufs[fd]);
// 	// printf("bufs after read: %s(BUF_END)\n", bufs[fd]);
// 	return (line);
// }
// int	get_line(int fd, char *line)
// {
// 	static int	lnumber[10];

// 	line = get_next_line_DEBUG(fd);
// 	if (line == NULL)
// 		lnumber[fd] = 0;
// 	else
// 		lnumber[fd]++;
// 	printf("fd:%d / line:%d: line read: %s(EOL)\n", fd, lnumber[fd], line);
// 	// free(line);
// 	// lseek(fd, 5, SEEK_CUR);
// 	printf("%c", '\n');
// 	return (line != NULL);
// }
// int	main(int ac, char **av)
// {
// 	int		fd;
// 	int		fd01;
// 	int		fd02;
// 	char	*line;
// 	int		sign;

// 	fd = open("./testfile/test_nN.txt", O_RDONLY);
// 	fd01 = open("./testfile/test_42.txt", O_RDONLY);
// 	fd02 = open("./testfile/test_tmp.txt", O_RDONLY);
// 	printf("called read(%d, buf, BUFFER_SIZE=%d)\n\n", fd, BUFFER_SIZE);
// 	line = "";
// 	sign = 1;
// 	while (sign)
// 	{
// 		// line = get_line(fd, line, lnumber);
// 		// line = get_line(fd01, line, lnumber);
// 		// line = get_line(fd02, line, lnumber);
// 		sign = get_line(fd, line);
// 		sign += get_line(fd01, line);
// 		sign += get_line(fd02, line);
// 		printf("---\n\n");
// 	}
// 	printf("EOF!");
// 	// free(line);
// 	close(fd);
// 	close(fd01);
// 	close(fd02);
// 	return (0);
// }
