/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:57:25 by anakin            #+#    #+#             */
/*   Updated: 2025/01/24 17:47:13 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*find_newline(int fd, char *str)
{
	char	*buff;
	int		rd_byte;

	buff = (char *)gnl_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (NULL);
	rd_byte = 1;
	while (!gnl_strchr(buff, '\n') && rd_byte != 0)
	{
		rd_byte = read(fd, buff, BUFFER_SIZE);
		if (rd_byte == -1)
			return (free(str), free(buff), NULL);
		buff[rd_byte] = '\0';
		str = gnl_strjoin(str, buff);
	}
	free(buff);
	if (!*str)
		return (free(str), NULL);
	return (str);
}

char	*make_line(char *txt)
{
	char	*newline;
	int		i;

	i = 0;
	while (txt[i] != '\0' && txt[i] != '\n')
		i++;
	newline = (char *)malloc(sizeof(char) * (i + 2));
	if (!newline)
		return (NULL);
	i = 0;
	while (txt[i] != '\n' && txt[i] != '\0')
	{
		newline[i] = txt[i];
		i++;
	}
	newline[i] = '\n';
	newline[i + 1] = '\0';
	return (newline);
}

char	*next_text(char *text)
{
	size_t	i;
	size_t	j;
	char	*newt;

	if (!(gnl_strchr(text, '\n')) || !text)
	{
		return (NULL);
	}
	i = 0;
	while (text[i] != '\n' && text[i] != '\0')
		i++;
	newt = (char *)malloc(sizeof(char) * (gnl_strlen(text) - i + 1));
	if (!newt)
		return (NULL);
	i++;
	j = 0;
	while (text[i] != '\0')
		newt[j++] = text[i++];
	newt[j] = '\0';
	free(text);
	return (newt);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*text;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	text = find_newline(fd, text);
	if (!text)
	{
		return (NULL);
	}
	if (gnl_strchr(text, '\n'))
		line = make_line(text);
	else
		line = text;
	text = next_text(text);
	return (line);
}
