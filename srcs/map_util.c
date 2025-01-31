/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:11:43 by soaoki            #+#    #+#             */
/*   Updated: 2025/02/01 03:13:41 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**make_game_map(t_map *config_file)
{
	char	**map;
	int		array_size;
	int		i;
	int		start;

	array_size = (config_file->height - config_file->map_h);
	map = ft_calloc(sizeof(char *), array_size +1);
	i = 0;
	start = config_file ->map_h;
	while (i < array_size)
		map[i++] = ft_strdup(config_file->mapinfo[start ++]);
	map[i] = NULL;
	return (map);
}

void	map_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	if (dst == NULL || src == NULL)
		return ;
	while (src[i] != '\0')
	{
		if (src[i] == '\n')
			dst[i] = '2';
		else
			dst[i] = src[i];
		i++;
	}
}

char	**make_validation_map(char **map)
{
	int		max_len;
	int		num_array;
	int		i;
	char	**v_map;

	max_len = get_maxarray_index(map);
	num_array = count_strarray(map);
	v_map = ft_calloc(sizeof(char *), (num_array +1));
	i = 0;
	while (i < num_array)
	{
		v_map[i] = ft_calloc(sizeof(char), (max_len + 1));
		ft_memset(v_map[i], '3', max_len);
		v_map[i][max_len] = '\0';
		map_strcpy(v_map[i], map[i]);
		i ++;
	}
	v_map [i] = NULL;
	wp_free(&map);
	return (v_map);
}
