/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:43:49 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/24 13:49:57 by hauchida         ###   ########.fr       */
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

static void	draw_line(t_vector begin, t_vector end, int color)
{
	t_data	*data;
	double	slope;
	double	intercept;
	int		is_larger;

	data = get_t_data();
	slope = (end.y - begin.y) / (end.x - begin.x);
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

static void	calc_player_way(t_ray ray1, t_ray ray2, t_ray ray3)
{
	t_player	*player;
	t_vector	*hitpos;
	t_vector	beam_way;
	double		left_angle;
	double		change_angle;
	double		wallDist;
	double		lineHeight;

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
	// fov angle change
	while (left_angle < player->fov)
	{
		beam_way = get_beam(left_angle);
		draw_line(player->pos, beam_way, create_trgb(1, 255, 255, 255));
		left_angle += player->angle;
		hitpos = calc_intersection(ray1, (t_ray){player->pos, beam_way});
		if (!hitpos)
			continue ;
		hitpos = calc_intersection(ray2, (t_ray){player->pos, beam_way});
		if (!hitpos)
			continue ;
		hitpos = calc_intersection(ray3, (t_ray){player->pos, beam_way});
		if (!hitpos)
			continue ;

		
		wallDist = vector_mag(vector_sub(*hitpos, player->pos));
		lineHeight = 2800 / wallDist;
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
	t_ray ray1 = with2p((t_vector){50, 50}, (t_vector){100, 300});
	t_ray ray2 = with2p((t_vector){100, 300}, (t_vector){250, 200});
	t_ray ray3 = with2p((t_vector){250, 200}, (t_vector){50, 50});

	draw_line(ray_begin(ray1), ray_end(ray1), create_trgb(1, 255, 255, 255));
	draw_line(ray_begin(ray2), ray_end(ray2), create_trgb(1, 255, 255, 255));
	draw_line(ray_begin(ray3), ray_end(ray3), create_trgb(1, 255, 255, 255));

	draw_point(player->pos);

	calc_player_way(ray1, ray2, ray3);
	draw_line(player->pos, player->way, create_trgb(1, 255, 255, 255));

	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}