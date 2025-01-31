/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:03:08 by soaoki            #+#    #+#             */
/*   Updated: 2025/02/01 03:42:11 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_emptyline(char **map, int i)
{
	while (map[i] != NULL)
	{
		if (is_emptyline(map[i]))
		{
			print_error("Map information must not contain blank lines");
			return (1);
		}
		i ++;
	}
	return (0);
}

int	check_map_char(char **map, int i)
{
	int	j;

	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W'
				&& map[i][j] != 'E' && map[i][j] != '\n')
			{
				print_error("invalid character");
				return (1);
			}
			j ++;
		}
		i ++;
	}
	return (0);
}

int	check_map_start(t_config *config, char **map, int i)
{
	int	j;

	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				if (config->p_count == 0)
				{
					config->p_count++;
					config->x_position = j;
					config->y_position = i;
					config->p_direction = map[i][j];
				}
				else
					return (print_error("start position is one"), 1);
			}
			j ++;
		}
		i ++;
	}
	return (0);
}

void	validation_map(t_config *config, t_map *config_file, int i)
{
	char	**dup_map;
	char	**v_map;

	while (is_emptyline(config_file->mapinfo[i]))
		i++;
	config_file->map_h = i;
	if (check_map_emptyline(config_file->mapinfo, i)
		|| check_map_char(config_file->mapinfo, i)
		|| check_map_start(config, config_file->mapinfo, i)
		|| !config->p_count)
	{
		if (!config->p_count)
			print_error("start position is one");
		free_exit(config, config_file);
	}
	config->y_position = config->y_position - config_file->map_h;
	config->map.mapinfo = make_game_map(config_file);
	dup_map = make_game_map(config_file);
	v_map = make_validation_map(dup_map);
	if (!check_surroundwall(v_map))
	{
		free_exit(config, config_file);
	}
	wp_free(&v_map);
}
