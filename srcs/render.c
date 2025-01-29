/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:43:49 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/30 03:04:17 by hauchida         ###   ########.fr       */
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

static void	draw_texture(double hit_x, double hit_y, int line_height,
		int start_y, int i)
{
	t_data			*data;
	t_texture_img	*texture_img;
	int				end;
	int				texX;
	int				texY;
	double			step;
	double			texPos;

	texture_img = get_texture_img();
	data = get_t_data();
	step = 1.0 * texture_img[NORTH].height / line_height;
	hit_x -= floor(hit_x);
	texX = (int)(hit_x * (double)texture_img[NORTH].width);
	texPos = (hit_y - (HEIGHT / 2) + (line_height / 2)) * step;
	end = start_y + line_height;
	while (start_y < end)
	{
		texY = (int)texPos & (texture_img[NORTH].height - 1);
		texPos += step;
		my_mlx_pixel_put(&data->img, i, start_y,
			(int)get_texture_pixel_color(texture_img[NORTH], texX, texY));
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

// static void	draw_line(t_vector begin, t_vector end, int color)
// {
// 	t_data	*data;
// 	double	slope;
// 	double	intercept;
// 	int		is_larger;

// 	data = get_t_data();
// 	if (end.x - begin.x != 0)
// 		slope = (end.y - begin.y) / (end.x - begin.x);
// 	else
// 	{
// 		draw_vertical_line(begin, end, color);
// 		return ;
// 	}
// 	intercept = begin.y - (slope * begin.x);
// 	if (begin.x < end.x)
// 		is_larger = 0;
// 	else
// 		is_larger = 1;
// 	while (1)
// 	{
// 		my_mlx_pixel_put(&data->img, begin.x, ((slope * begin.x) + intercept),
// 			color);
// 		if (!is_larger && begin.x < end.x)
// 			begin.x++;
// 		else if (is_larger && begin.x > end.x)
// 			begin.x--;
// 		else
// 			break ;
// 	}
// }

// static t_vector	get_beam(double angle)
// {
// 	t_player	*player;
// 	double		x;
// 	double		y;

// 	player = get_player();
// 	x = ((player->way.x - player->pos.x) * cos(angle)) - ((player->way.y
// 				- player->pos.y) * sin(angle)) + player->pos.x;
// 	y = ((player->way.x - player->pos.x) * sin(angle)) + ((player->way.y
// 				- player->pos.y) * cos(angle)) + player->pos.y;
// 	return ((t_vector){x, y});
// }

// static void	render_wall_line(t_vector *hitpos, int index)
// {
// 	t_player	*player;
// 	double		wall_dist;
// 	double		line_height;
// 	double		draw_start;
// 	double		draw_end;
// 	t_vector	line_begin;
// 	t_vector	line_end;

// 	if (!hitpos)
// 		return ;
// 	player = get_player();
// 	wall_dist = vector_mag(vector_sub(*hitpos, player->pos));
// 	line_height = HEIGHT * WIDTH / wall_dist;
// 	draw_start = -(line_height / 2) + HEIGHT / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	draw_end = line_height;
// 	if (draw_end >= HEIGHT)
// 		draw_end = HEIGHT;
// 	line_begin = (t_vector){index, draw_start};
// 	line_end = vector_add(line_begin, (t_vector){0, draw_end});
// 	// draw_texture(line_begin, line_end, *hitpos, line_height);
// 	draw_line(line_begin, line_end, create_trgb(1, 255, 0, 255));
// 	free(hitpos);
// }

// static t_vector	**calc_wall_intersection(t_square *square, t_ray beam,
// 		int *index)
// {
// 	int			i;
// 	t_vector	**hitpos;

// 	hitpos = (t_vector **)malloc(sizeof(t_vector *) * 2);
// 	hitpos[(*index)] = calc_intersection(square->top, beam);
// 	if (hitpos[(*index)] != NULL)
// 		(*index)++;
// 	hitpos[(*index)] = calc_intersection(square->down, beam);
// 	if (hitpos[(*index)] != NULL)
// 		(*index)++;
// 	if (*index == 2)
// 		return (hitpos);
// 	hitpos[(*index)] = calc_intersection(square->left, beam);
// 	if (hitpos[(*index)] != NULL && *index < 2)
// 		(*index)++;
// 	if (*index == 2)
// 		return (hitpos);
// 	hitpos[(*index)] = calc_intersection(square->right, beam);
// 	if (hitpos[(*index)] != NULL && *index < 2)
// 		(*index)++;
// 	return (hitpos);
// }

// static void	check_wall_hit(t_ray beam, int index)
// {
// 	int			i;
// 	t_square	*tmp;
// 	t_vector	**hitpos;

// 	tmp = *get_square();
// 	i = 0;
// 	while (tmp)
// 	{
// 		hitpos = calc_wall_intersection(tmp, beam, &i);
// 		if (i == 2)
// 		{
// 			if (vector_mag(vector_sub(*hitpos[0],
// 						beam.pos)) < vector_mag(vector_sub(*hitpos[1],
// 						beam.pos)))
// 				render_wall_line(hitpos[0], index);
// 			else
// 				render_wall_line(hitpos[1], index);
// 		}
// 		i = 0;
// 		free(hitpos);
// 		tmp = tmp->next;
// 	}
// }

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
	if (data->map[y][x] == '1')
		return (1);
	return (0);
}

// raycasting functions
void	draw_player_ray(t_player *player, t_data *data, double start_x, int i)
{
	double	cos_angle;
	double	sin_angle;
	double	ray_x;
	double	ray_y;
	double	dist;
	double	height;
	int		start_y;
	int		end;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->pos.x;
	ray_y = player->pos.y;
	while (!touch(ray_x, ray_y, data))
	{
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	dist = fixed_dist(player->pos.x, player->pos.y, ray_x, ray_y, player);
	height = (SQUARE_SIZE / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	draw_texture(ray_x, ray_y, height, start_y, i);
	// while (start_y < end)
	// {
	// 	my_mlx_pixel_put(&data->img, i, start_y, create_trgb(1, 255, 255, 255));
	// 	start_y++;
	// }
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