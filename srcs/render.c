/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:43:49 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/28 16:58:53 by hauchida         ###   ########.fr       */
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

static void	draw_vertical_line(t_vector begin, t_vector end, int color)
{
	t_data	*data;
	int		i;

	data = get_t_data();
	i = begin.y;
	while (i < end.y)
	{
		my_mlx_pixel_put(&data->img, begin.x, i, color);
		i++;
	}
}

static void	draw_texture(t_vector begin, t_vector end, t_vector hitpos,
		int lineHeight)
{
	t_data			*data;
	t_texture_img	*texture_img;
	int				i;
	int				texX;
	int				texY;
	double			step;
	double			texPos;

	texture_img = get_texture_img();
	data = get_t_data();
	step = 1.0 * texture_img[NORTH].height / lineHeight;
	hitpos.x -= floor(hitpos.x);
	texX = (int)(hitpos.x * (double)texture_img[NORTH].width);
	texPos = (hitpos.y - (HEIGHT / 2) + (lineHeight / 2)) * step;
	i = begin.y;
	while (i < end.y)
	{
		texY = (int)texPos & (texture_img[NORTH].height - 1);
		texPos += step;
		my_mlx_pixel_put(&data->img, begin.x, i,
			(int)get_texture_pixel_color(texture_img[NORTH], texX, texY));
		i++;
	}
}

static void	draw_horizontal_line(t_vector begin, t_vector end, int color)
{
	t_data	*data;
	int		i;

	data = get_t_data();
	i = begin.x;
	while (i < end.x)
	{
		my_mlx_pixel_put(&data->img, i, begin.y, color);
		i++;
	}
}

static void	draw_square(void)
{
	t_square	**top_square;
	t_square	*tmp;

	top_square = get_square();
	tmp = *top_square;
	while (tmp)
	{
		draw_horizontal_line(ray_begin((tmp)->top), ray_end((tmp)->top),
			create_trgb(1, 255, 255, 255));
		draw_horizontal_line(ray_begin((tmp)->down), ray_end((tmp)->down),
			create_trgb(1, 255, 255, 255));
		draw_vertical_line(ray_begin((tmp)->left), ray_end((tmp)->left),
			create_trgb(1, 255, 255, 255));
		draw_vertical_line(ray_begin((tmp)->right), ray_end((tmp)->right),
			create_trgb(1, 255, 255, 255));
		tmp = tmp->next;
	}
}

static void	draw_line(t_vector begin, t_vector end, int color)
{
	t_data	*data;
	double	slope;
	double	intercept;
	int		is_larger;

	data = get_t_data();
	if (end.x - begin.x != 0)
		slope = (end.y - begin.y) / (end.x - begin.x);
	else
	{
		draw_vertical_line(begin, end, color);
		return ;
	}
	intercept = begin.y - (slope * begin.x);
	if (begin.x < end.x)
		is_larger = 0;
	else
		is_larger = 1;
	while (1)
	{
		my_mlx_pixel_put(&data->img, begin.x, ((slope * begin.x) + intercept),
			color);
		if (!is_larger && begin.x < end.x)
			begin.x++;
		else if (is_larger && begin.x > end.x)
			begin.x--;
		else
			break ;
	}
}

static t_vector	get_beam(double angle)
{
	t_player	*player;
	double		x;
	double		y;

	player = get_player();
	x = ((player->way.x - player->pos.x) * cos(angle)) - ((player->way.y
				- player->pos.y) * sin(angle)) + player->pos.x;
	y = ((player->way.x - player->pos.x) * sin(angle)) + ((player->way.y
				- player->pos.y) * cos(angle)) + player->pos.y;
	return ((t_vector){x, y});
}

static void	render_wall_line(t_vector *hitpos, int index)
{
	t_player	*player;
	double		wall_dist;
	double		line_height;
	double		draw_start;
	double		draw_end;
	t_vector	line_begin;
	t_vector	line_end;

	if (!hitpos)
		return ;
	player = get_player();
	wall_dist = vector_mag(vector_sub(*hitpos, player->pos));
	line_height = 60000 / wall_dist;
	draw_start = -(line_height / 2) + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT;
	line_begin = (t_vector){index, draw_start};
	line_end = vector_add(line_begin, (t_vector){0, draw_end});
	draw_texture(line_begin, line_end, *hitpos, line_height);
	// draw_line(line_begin, line_end, create_trgb(1, 255, 255, 255));
	free(hitpos);
}

static t_vector	**calc_wall_intersection(t_square *square, t_ray beam,
		int *index)
{
	int			i;
	t_vector	**hitpos;

	hitpos = (t_vector **)malloc(sizeof(t_vector *) * 2);
	hitpos[(*index)] = calc_intersection(square->top, beam);
	if (hitpos[(*index)] != NULL)
		(*index)++;
	hitpos[(*index)] = calc_intersection(square->down, beam);
	if (hitpos[(*index)] != NULL)
		(*index)++;
	if (*index == 2)
		return (hitpos);
	hitpos[(*index)] = calc_intersection(square->left, beam);
	if (hitpos[(*index)] != NULL && *index < 2)
		(*index)++;
	if (*index == 2)
		return (hitpos);
	hitpos[(*index)] = calc_intersection(square->right, beam);
	if (hitpos[(*index)] != NULL && *index < 2)
		(*index)++;
	return (hitpos);
}

static void	check_wall_hit(t_ray beam, int index)
{
	int			i;
	t_square	*tmp;
	t_vector	**hitpos;

	tmp = *get_square();
	i = 0;
	while (tmp)
	{
		hitpos = calc_wall_intersection(tmp, beam, &i);
		if (i == 2)
		{
			if (vector_mag(vector_sub(*hitpos[0],
						beam.pos)) < vector_mag(vector_sub(*hitpos[1],
						beam.pos)))
				render_wall_line(hitpos[0], index);
			else
				render_wall_line(hitpos[1], index);
		}
		i = 0;
		free(hitpos);
		tmp = tmp->next;
	}
}

static void	calc_player_way(void)
{
	t_player	*player;
	t_vector	*hitpos;
	t_vector	beam_pos;
	double		left_angle;
	double		change_angle;
	int			i;
	int			beam_total;

	player = get_player();
	left_angle = -player->fov;
	if (player->is_left_angle)
	{
		player->is_left_angle = 0;
		change_angle = -player->angle;
	}
	else if (player->is_right_angle)
	{
		player->is_right_angle = 0;
		change_angle = player->angle;
	}
	i = 0;
	beam_total = WIDTH;
	// fov angle change
	while (left_angle < player->fov)
	{
		beam_pos = get_beam(left_angle);
		draw_line(player->pos, beam_pos, create_trgb(1, 255, 255, 255));
		left_angle += player->fov / beam_total;
		i++;
		check_wall_hit(with2p(player->pos, beam_pos), i);
	}
	// center angle change
	player->way = get_beam(change_angle);
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
	draw_square();
	draw_point(player->pos);
	calc_player_way();
	draw_line(player->pos, player->way, create_trgb(1, 255, 255, 255));
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}