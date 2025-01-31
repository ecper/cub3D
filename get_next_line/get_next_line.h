/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:59:14 by anakin            #+#    #+#             */
/*   Updated: 2025/01/24 17:48:16 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *left_str, char *buff);
void	*gnl_calloc(size_t nmemb, size_t size);
size_t	gnl_strlen(const char *str);
char	*make_line(char *txt);
char	*find_newline(int fd, char *str);
char	*next_text(char *text);
char	*get_next_line(int fd);

#endif
