/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:57:48 by anakin            #+#    #+#             */
/*   Updated: 2025/01/24 18:13:07 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, int c)
{
	char	*buff;

	buff = (char *)s;
	while (*buff)
	{
		if (*buff == (char)c)
			return (buff);
		buff++;
	}
	if ((char)c == '\0')
		return (buff);
	return (0);
}

void	*gnl_calloc(size_t nmemb, size_t size)
{
	void			*p;
	size_t			i;
	unsigned char	*dest;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb && size && nmemb > SIZE_MAX / size)
		return (0);
	p = malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	dest = (unsigned char *)p;
	i = 0;
	while (i < nmemb * size)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}

char	*gnl_strjoin(char *text, char *buff_s)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!text)
	{
		text = (char *)malloc(1 * sizeof(char));
		text[0] = '\0';
	}
	if (!text || !buff_s)
		return (NULL);
	str = malloc(sizeof(char) * ((gnl_strlen(text) + gnl_strlen(buff_s)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (text)
		while (text[++i] != '\0')
			str[i] = text[i];
	while (buff_s[j] != '\0')
		str[i++] = buff_s[j++];
	str[gnl_strlen(text) + gnl_strlen(buff_s)] = '\0';
	free(text);
	return (str);
}

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}
