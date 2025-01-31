/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:43:49 by hauchida          #+#    #+#             */
/*   Updated: 2025/02/01 00:03:34 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_color(void)
{
	t_data	*data;
	int		w;
	int		h;

	data = get_t_data();
	w = 0;
	h = 0;
	while (w < WIDTH)
	{
		h = 0;
		while (h < HEIGHT)
		{
			my_mlx_pixel_put(&data->img, w, h, create_trgb(1, 0, 0, 0));
			h++;
		}
		w++;
	}
}

static int	check_texture_dir(double raydir_x, double raydir_y, int side)
{
	if (raydir_y >= 0 && ((raydir_x >= 0 || raydir_x <= 0)) && side == 1)
		return (NORTH);
	else if (raydir_x >= 0 && (raydir_y >= 0 || raydir_y <= 0) && side == 0)
		return (WEST);
	else if (raydir_x <= 0 && (raydir_y <= 0 || raydir_y >= 0) && side == 0)
		return (EAST);
	else
		return (SOUTH);
}

static void	draw_texture(t_player_ray player_ray, int i, int side)
{
	t_data			*data;
	t_texture_img	*texture_img;
	t_player		*player;
	double			wall_x;
	int				texX;
	int				texY;
	double			step;
	double			tex_pos;
	int				color;
	int				texture_dir;

	texture_img = get_texture_img();
	data = get_t_data();
	player = get_player();
	texture_dir = check_texture_dir(player_ray.raydir_x, player_ray.raydir_y, side);
	step = 1.0 * texture_img[texture_dir].height / player_ray.line_height;
	// 壁のどこに当たったか計算
	if (side == 0)
		wall_x = (player->pos.y) + player_ray.perp_wall_dist * (player_ray.raydir_y);
	else
		wall_x = (player->pos.x) + player_ray.perp_wall_dist * (player_ray.raydir_x);
	wall_x -= floor((wall_x));
	// X座標の計算
	texX = (int)(wall_x * (double)texture_img[texture_dir].width);
	// 壁の向きに応じて反転
	if (side == 0 && player_ray.raydir_x > 0)
		texX = texture_img[texture_dir].width - texX - 1;
	if (side == 1 && player_ray.raydir_y < 0)
		texX = texture_img[texture_dir].width - texX - 1;
	tex_pos = (player_ray.start_y - (HEIGHT / 2) + (player_ray.line_height / 2)) * step;
	while (player_ray.start_y < player_ray.end_y)
	{
		texY = (int)tex_pos & (texture_img[texture_dir].height - 1);
		tex_pos += step;
		color = get_texture_pixel_color(texture_img[texture_dir], texX, texY);
		my_mlx_pixel_put(&data->img, i, player_ray.start_y, color);
		player_ray.start_y++;
	}
}

static void	draw_vertical_line(int start, int end, int x, int color)
{
	t_data	*data;
	int		i;

	data = get_t_data();
	i = start;
	while (i < end)
	{
		my_mlx_pixel_put(&data->img, x, i, color);
		i++;
	}
}

static void	draw_horizontal_line(int start, int end, int y, int color)
{
	t_data	*data;
	int		i;

	data = get_t_data();
	i = start;
	while (i < end)
	{
		my_mlx_pixel_put(&data->img, i, y, color);
		i++;
	}
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

int	touch(int x, int y, t_data *data)
{
	if (data->map[y][x] == '1' || data->map[y][x] == '2'
		|| data->map[y][x] == '3' || data->map[y][x] == '4')
		return (1);
	return (0);
}

int	get_color(double px, double py, t_data *data)
{
	int	x;
	int	y;

	x = px;
	y = py;
	if (data->map[y][x] == '1')
		return (create_trgb(1, 255, 255, 255));
	else if (data->map[y][x] == '2')
		return (create_trgb(1, 255, 0, 0));
	else if (data->map[y][x] == '3')
		return (create_trgb(1, 0, 255, 0));
	else
		return (create_trgb(1, 0, 0, 255));
}

static void	draw_celling(int start_y, int x)
{
	t_data	*data;
	int		celling_start;
	int		celling_end;

	celling_start = 0;
	celling_end = start_y;
	data = get_t_data();
	while (celling_start < celling_end)
	{
		my_mlx_pixel_put(&data->img, x, celling_start, create_trgb(1, 255, 255,
				0));
		celling_start++;
	}
}

static void	draw_floor(int end_y, int x)
{
	t_data	*data;
	int		floor_start;
	int		floor_end;

	floor_start = end_y;
	floor_end = HEIGHT;
	data = get_t_data();
	while (floor_start < floor_end)
	{
		my_mlx_pixel_put(&data->img, x, floor_start, create_trgb(1, 0, 255, 0));
		floor_start++;
	}
}

// raycasting functions
void	draw_player_ray(t_player *player, t_data *data, double start_x, int i)
{
	t_player_ray	player_ray;
	int				side;
	int				map_x;
	int				map_y;

	// double	raydir_x;
	// double	raydir_y;
	// double	ray_x;
	// double	ray_y;
	// double	delta_dist_x;
	// double	delta_dist_y;
	// double	dist_x;
	// double	dist_y;
	// double	step_x;
	// double	step_y;
	// double	perp_wall_dist;
	// int		line_height;
	// int		start_y;
	// int		end_y;
	// int		side;
	map_x = (int)(player->pos.x);
	map_y = (int)(player->pos.y);
	player_ray.raydir_x = cos(start_x);
	player_ray.raydir_y = sin(start_x);
	player_ray.ray_x = player->pos.x;
	player_ray.ray_y = player->pos.y;
	player_ray.delta_dist_x = (player_ray.raydir_x == 0) ? 1e30 : fabs(1
			/ player_ray.raydir_x);
	player_ray.delta_dist_y = (player_ray.raydir_y == 0) ? 1e30 : fabs(1
			/ player_ray.raydir_y);
	player_ray.step_x = (player_ray.raydir_x > 0) ? 1 : -1;
	player_ray.step_y = (player_ray.raydir_y > 0) ? 1 : -1;
	player_ray.dist_x = (player_ray.raydir_x > 0) ? (map_x + 1.0
			- player->pos.x) * player_ray.delta_dist_x : (player->pos.x - map_x)
		* player_ray.delta_dist_x;
	player_ray.dist_y = (player_ray.raydir_y > 0) ? (map_y + 1.0
			- player->pos.y) * player_ray.delta_dist_y : (player->pos.y - map_y)
		* player_ray.delta_dist_y;
	while (!touch(map_x, map_y, data))
	{
		if (player_ray.dist_x < player_ray.dist_y)
		{
			player_ray.dist_x += player_ray.delta_dist_x;
			map_x += player_ray.step_x;
			side = 0;
		}
		else
		{
			player_ray.dist_y += player_ray.delta_dist_y;
			map_y += player_ray.step_y;
			side = 1;
		}
	}
	if (side == 0)
		player_ray.perp_wall_dist = player_ray.dist_x - player_ray.delta_dist_x;
	else
		player_ray.perp_wall_dist = player_ray.dist_y - player_ray.delta_dist_y;
	player_ray.line_height = (int)(HEIGHT / player_ray.perp_wall_dist) * 2;
	player_ray.start_y = -(player_ray.line_height / 2) + (HEIGHT / 2);
	if (player_ray.start_y < 0)
		player_ray.start_y = 0;
	player_ray.end_y = (player_ray.line_height / 2) + (HEIGHT / 2);
	if (player_ray.end_y >= HEIGHT)
		player_ray.end_y = HEIGHT - 1;
	draw_celling(player_ray.start_y, i);
	draw_texture(player_ray, i, side);
	draw_floor(player_ray.end_y, i);
}

static void	calc_player_way(void)
{
	t_player	*player;
	t_data		*data;
	t_vector	*hitpos;
	t_vector	beam_pos;
	double		start;
	double		change_angle;
	int			i;

	player = get_player();
	data = get_t_data();
	start = player->angle - M_PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_player_ray(player, data, start, i);
		start += player->fov / WIDTH;
		i++;
	}
}

int	render(t_data *data)
{
	t_player *player = get_player();
	clear_color();
	calc_player_way();
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}