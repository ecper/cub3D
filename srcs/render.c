/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:43:49 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/31 03:08:53 by hauchida         ###   ########.fr       */
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

// static void	draw_texture(double hit_x, double hit_y, int line_height,
// 		int start_x, int start_y, int i)
// {
// 	t_data			*data;
// 	t_texture_img	*texture_img;
// 	int				end;
// 	double			wall_x;
// 	int				texX;
// 	int				texY;
// 	double			step;
// 	double			texPos;

// 	texture_img = get_texture_img();
// 	data = get_t_data();
// 	step = 1.0 * texture_img[NORTH].height / line_height;
// 	if (hit_x < hit_y)
// 		wall_x = hit_y - floor(hit_y);
// 	else
// 		wall_x = hit_x - floor(hit_x);
// 	texX = (int)(wall_x * (double)texture_img[NORTH].width);
// 	// if (texX < 0)
// 	// 	texX = 0;
// 	// if (texX >= (double)texture_img[NORTH].width)
// 	// 	texX = (double)texture_img[NORTH].width - 1;
// 	if (hit_x < hit_y && cos(start_x) > 0)
// 		texX = (double)texture_img[NORTH].width - texX - 1;
// 	else if (hit_x > hit_y && sin(start_x) < 0)
// 		texX = (double)texture_img[NORTH].width - texX - 1;
// 	texPos = (start_y - (HEIGHT / 2) + (line_height / 2)) * step;
// 	end = start_y + line_height;
// 	while (start_y < end)
// 	{
// 		texY = (int)texPos & (texture_img[NORTH].height - 1);
// 		// printf("texX: %d, texY: %d\n", texX, texY);
// 		// fflush(0);
// 		texPos += step;
// 		my_mlx_pixel_put(&data->img, i, start_y,
// 			(int)get_texture_pixel_color(texture_img[NORTH], texX, texY));
// 		start_y++;
// 	}
// }

static void	draw_texture(double perp_wall_dist, int line_height,
		double raydir_x, double raydir_y, int start_y, int i, int side)
{
	t_data			*data;
	t_texture_img	*texture_img;
	t_player		*player;
	int				end;
	double			wall_x;
	int				texX;
	int				texY;
	double			step;
	double			tex_pos;
	int				color;

	texture_img = get_texture_img();
	data = get_t_data();
	player = get_player();
	step = 1.0 * texture_img[NORTH].height / line_height;
	// 壁のどこに当たったか計算
	if (side == 0)
		wall_x = (double)((int)(player->pos.y / SQUARE_SIZE)) + perp_wall_dist
			* (raydir_y);
	else
		wall_x = (double)((int)(player->pos.x / SQUARE_SIZE)) + perp_wall_dist
			* (raydir_x);
	wall_x -= floor(wall_x);
	// printf("wall_x: %f\n", wall_x);
	// X座標の計算
	texX = (int)(wall_x * (double)texture_img[NORTH].width);
	// printf("texX: %d, texY: %d\n", texX, texY);
	// fflush(0);
	// 壁の向きに応じて反転
	if (side == 0 && raydir_x > 0)
		texX = texture_img[NORTH].width - texX - 1;
	if (side == 1 && raydir_y < 0)
		texX = texture_img[NORTH].width - texX - 1;
	tex_pos = (start_y - (HEIGHT / 2) + (line_height / 2)) * step;
	end = start_y + line_height;
	while (start_y < end)
	{
		texY = (int)tex_pos & (texture_img[NORTH].height - 1);
		tex_pos += step;
		color = get_texture_pixel_color(texture_img[NORTH], texX, texY);
		my_mlx_pixel_put(&data->img, i, start_y, color);
		start_y++;
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

static void	draw_square(int x, int y, int size, int color)
{
	t_data	*data;
	int		i;

	data = get_t_data();
	draw_vertical_line(y, size, x, color);
	draw_horizontal_line(x, size, y, color);
	draw_vertical_line(y, size, x + size, color);
	draw_horizontal_line(x, y + size, y, color);
}

static void	draw_map(void)
{
	char	**map;
	int		color;
	t_data	*data;

	data = get_t_data();
	map = data->map;
	color = 0x0000FF;
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE,
					color);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

double	fixed_dist(double x1, double y1, double x2, double y2, t_player *player)
{
	double	delta_x;
	double	delta_y;
	double	angle;
	double	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - player->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

int	touch(double px, double py, t_data *data)
{
	int	x;
	int	y;

	x = px / SQUARE_SIZE;
	y = py / SQUARE_SIZE;
	if (data->map[y][x] == '1' || data->map[y][x] == '2'
		|| data->map[y][x] == '3' || data->map[y][x] == '4')
		return (1);
	return (0);
}

int	get_color(double px, double py, t_data *data)
{
	int	x;
	int	y;

	x = px / SQUARE_SIZE;
	y = py / SQUARE_SIZE;
	if (data->map[y][x] == '1')
		return (create_trgb(1, 255, 255, 255));
	else if (data->map[y][x] == '2')
		return (create_trgb(1, 255, 0, 0));
	else if (data->map[y][x] == '3')
		return (create_trgb(1, 0, 255, 0));
	else
		return (create_trgb(1, 0, 0, 255));
}

// raycasting functions
void	draw_player_ray(t_player *player, t_data *data, double start_x, int i)
{
	double	raydir_x;
	double	raydir_y;
	double	ray_x;
	double	ray_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	dist_x;
	double	dist_y;
	double	step_x;
	double	step_y;
	double	perp_wall_dist;
	double	dist;
	double	height;
	int		start_y;
	int		end;
	int		side;

	raydir_x = cos(start_x);
	raydir_y = sin(start_x);
	ray_x = player->pos.x;
	ray_y = player->pos.y;
	delta_dist_x = sqrt(1 + (raydir_y * raydir_y) / (raydir_x * raydir_x));
	delta_dist_y = sqrt(1 + (raydir_x * raydir_x) / (raydir_y * raydir_y));
	// // **X方向とY方向のステップを計算**
	step_x = (raydir_x > 0) ? 1 : -1;
	step_y = (raydir_y > 0) ? 1 : -1;
	// // **次のX軸の壁とY軸の壁に到達する距離を計算**
	dist_x = (step_x > 0) ? (ceil(ray_x) - ray_x) / raydir_x : (ray_x
			- floor(ray_x)) / -raydir_x;
	dist_y = (step_y > 0) ? (ceil(ray_y) - ray_y) / raydir_y : (ray_y
			- floor(ray_y)) / -raydir_y;
	while (!touch(ray_x, ray_y, data))
	{
		if (dist_x < dist_y)
		{
			dist_x += delta_dist_x;
			ray_x += step_x;
			side = 0; // X軸にぶつかった
		}
		else
		{
			dist_y += delta_dist_y;
			ray_y += step_y;
			side = 1; // Y軸にぶつかった
		}
	}
	if (side == 0)
		perp_wall_dist = dist_x - delta_dist_x;
	else
		perp_wall_dist = dist_y - delta_dist_y;
	dist = fixed_dist(player->pos.x, player->pos.y, ray_x, ray_y, player);
	height = (HEIGHT / perp_wall_dist) * (WIDTH) / 10 ;
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	if (data->map[(int)(ray_y / SQUARE_SIZE)][(int)(ray_x
			/ SQUARE_SIZE)] == '2')
		draw_texture(perp_wall_dist / SQUARE_SIZE, height, raydir_x, raydir_y, start_y, i,
			side);
	else
		while (start_y < end)
		{
			my_mlx_pixel_put(&data->img, i, start_y, get_color(ray_x, ray_y,
					data));
			start_y++;
		}
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

static void	draw_point(t_vector pos)
{
	t_data	*data;

	data = get_t_data();
	my_mlx_pixel_put(&data->img, pos.x, pos.y, create_trgb(1, 255, 255, 255));
}

int	render(t_data *data)
{
	t_player *player = get_player();
	clear_color();
	// draw_map();
	// draw_square();
	// draw_point(player->pos);
	calc_player_way();
	// draw_line(player->pos, player->way, create_trgb(1, 255, 255, 255));
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}