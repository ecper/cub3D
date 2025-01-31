/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_surround.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:04:30 by soaoki            #+#    #+#             */
/*   Updated: 2025/02/01 03:41:40 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_horizon(char **map, int x, int y)
{
	int	i;

	i = 0;
	while (i <= x)
	{
		if (map[0][i] == '0' || map[0][i] == 'N' || map[0][i] == 'S'
		|| map[0][i] == 'W' || map[0][i] == 'E')
			return (1);
		if (map[y][i] == '0' || map[y][i] == 'N' || map[y][i] == 'S'
		|| map[y][i] == 'W' || map[y][i] == 'E')
			return (1);
		i++;
	}
	return (0);
}

int	check_verticall(char **map, int x, int y)
{
	int	i;

	i = 0;
	while (i < y)
	{
		if (map[i][0] == '0' || map[i][0] == 'N' || map[i][0] == 'S'
		|| map[i][0] == 'W' || map[i][0] == 'E')
			return (1);
		if (map[i][x] == '0' || map[i][x] == 'N' || map[i][x] == 'S'
		|| map[i][x] == 'W' || map[i][x] == 'E')
			return (1);
		i ++;
	}
	return (0);
}

int	see_aroundchar(char **map, int point_x, int point_y)
{
	if (map[point_y + 1][point_x] == ' ' || map[point_y + 1][point_x] == '2'
		||map[point_y + 1][point_x] == '3')
		return (1);
	else if (map[point_y -1][point_x] == ' ' || map[point_y -1][point_x] == '2'
		||map[point_y - 1][point_x] == '3')
		return (1);
	else if (map[point_y][point_x +1] == ' ' || map[point_y][point_x +1] == '2'
		||map[point_y][point_x +1] == '3')
		return (1);
	else if (map[point_y][point_x -1] == ' ' || map[point_y][point_x -1] == '2'
		||map[point_y][point_x -1] == '3')
		return (1);
	else
		return (0);
}

int	check_inter(char **map, int x, int y)
{
	int		i;
	int		j;

	i = 1;
	while (i < y)
	{
		j = 1;
		while (j < x)
		{
			if ((map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				&& see_aroundchar(map, j, i))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_surroundwall(char **map)
{
	int		x;
	int		y;

	x = get_maxarray_index(map) -1;
	y = count_strarray(map) - 1;
	if (check_horizon(map, x, y) || check_verticall(map, x, y)
		||check_inter(map, x, y))
	{
		print_error("the map must be surrounded by walls");
		return (0);
	}
	return (1);
}
