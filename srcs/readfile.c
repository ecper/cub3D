/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:03:29 by soaoki            #+#    #+#             */
/*   Updated: 2025/02/01 04:20:48 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	add_line(t_map *map, char *line)
{
	char	**tmp;
	int		i;

	if (!line)
		return (0);
	map->height++;
	tmp = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!tmp)
	{
		free(line);
		return (0);
	}
	tmp[map->height] = NULL;
	i = 0;
	while (i < map->height - 1)
	{
		tmp[i] = ft_strdup(map->mapinfo[i]);
		i++;
	}
	tmp[i] = line;
	if (map->mapinfo)
		wp_free(&(map->mapinfo));
	map->mapinfo = tmp;
	return (1);
}

t_map	*read_configfile(int fd)
{
	t_map	*buff;
	char	*readline;

	buff = ft_calloc(sizeof(t_map), 1);
	if (!buff)
		return (NULL);
	readline = get_next_line(fd);
	while (readline != NULL)
	{
		if (!add_line(buff, readline))
		{
			free(readline);
			close(fd);
			return (0);
		}
		readline = get_next_line(fd);
	}
	close(fd);
	if (!buff || !(buff->mapinfo))
	{	
		print_error("Could not load map");
		exit (1);
	}
	return (buff);
}
