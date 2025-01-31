/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:50:00 by hauchida          #+#    #+#             */
/*   Updated: 2025/02/01 02:05:29 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_delta_dist(t_player_ray *player_ray)
{
	if (player_ray->raydir_x == 0)
		player_ray->delta_dist_x = 1e30;
	else
		player_ray->delta_dist_x = fabs(1 / player_ray->raydir_x);
	if (player_ray->raydir_y == 0)
		player_ray->delta_dist_y = 1e30;
	else
		player_ray->delta_dist_y = fabs(1 / player_ray->raydir_y);
}

static void	init_player_dist_step(t_player_ray *player_ray, int map_x,
		int map_y, t_player *player)
{
	if (player_ray->raydir_x > 0)
	{
		player_ray->step_x = 1;
		player_ray->dist_x = (map_x + 1.0 - player->pos.x)
			* player_ray->delta_dist_x;
	}
	else
	{
		player_ray->step_x = -1;
		player_ray->dist_x = (player->pos.x - map_x) * player_ray->delta_dist_x;
	}
	if (player_ray->raydir_y > 0)
	{
		player_ray->step_y = 1;
		player_ray->dist_y = (map_y + 1.0 - player->pos.y)
			* player_ray->delta_dist_y;
	}
	else
	{
		player_ray->step_y = -1;
		player_ray->dist_y = (player->pos.y - map_y) * player_ray->delta_dist_y;
	}
}

void	init_player_ray(t_player_ray *player_ray, int map_x, int map_y,
		double start_x)
{
	t_player	*player;

	player = get_player();
	player_ray->raydir_x = cos(start_x);
	player_ray->raydir_y = sin(start_x);
	player_ray->ray_x = player->pos.x;
	player_ray->ray_y = player->pos.y;
	init_delta_dist(player_ray);
	init_player_dist_step(player_ray, map_x, map_y, player);
}

static void	check_wall_hit_ray(t_data *data, t_player_ray *player_ray,
		int map_x, int map_y)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (player_ray->dist_x < player_ray->dist_y)
		{
			player_ray->dist_x += player_ray->delta_dist_x;
			map_x += player_ray->step_x;
			player_ray->side = 0;
		}
		else
		{
			player_ray->dist_y += player_ray->delta_dist_y;
			map_y += player_ray->step_y;
			player_ray->side = 1;
		}
		if (data->map[map_y][map_x] > '0')
			hit = 1;
	}
}

void	calc_player_ray(t_player_ray *player_ray, int map_x, int map_y,
		double start_x)
{
	t_data	*data;

	data = get_t_data();
	check_wall_hit_ray(data, player_ray, map_x, map_y);
	if (player_ray->side == 0)
		player_ray->perp_wall_dist = player_ray->dist_x
			- player_ray->delta_dist_x;
	else
		player_ray->perp_wall_dist = player_ray->dist_y
			- player_ray->delta_dist_y;
	player_ray->line_height = (int)(HEIGHT / player_ray->perp_wall_dist) * 2;
	player_ray->start_y = -(player_ray->line_height / 2) + (HEIGHT / 2);
	if (player_ray->start_y < 0)
		player_ray->start_y = 0;
	player_ray->end_y = (player_ray->line_height / 2) + (HEIGHT / 2);
	if (player_ray->end_y >= HEIGHT)
		player_ray->end_y = HEIGHT - 1;
}
