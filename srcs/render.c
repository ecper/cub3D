/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:43:49 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/23 18:19:57 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

static void calc_player_way(void)
{
	t_player *player = get_player();

	double x = ((player->way.x - player->pos.x) * cos(player->angle) * 10) - ((player->way.y - player->pos.y) * sin(player->angle) * 10);
	double y = ((player->way.x - player->pos.x) * sin(player->angle) * 10) + ((player->way.y - player->pos.y) * cos(player->angle) * 10);

	player->way.x = x;
	player->way.y = y;
}


static void	draw_point(t_vector pos)
{
	t_data	*data;

	data = get_t_data();
	my_mlx_pixel_put(&data->img, pos.x, pos.y, create_trgb(1, 255, 255, 255));
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	render(t_data *data)
{
	t_player *player = get_player();
	t_ray ray1 = with2p((t_vector){50, 50}, (t_vector){100, 300});
	t_ray ray2 = with2p((t_vector){100, 300}, (t_vector){250, 200});
	t_ray ray3 = with2p((t_vector){250, 200}, (t_vector){50, 50});

	draw_line(ray_begin(ray1), ray_end(ray1), create_trgb(1, 255, 255, 255));
	draw_line(ray_begin(ray2), ray_end(ray2), create_trgb(1, 255, 255, 255));
	draw_line(ray_begin(ray3), ray_end(ray3), create_trgb(1, 255, 255, 255));

	draw_point(player->pos);

	calc_player_way();
	draw_line(player->pos, player->way, create_trgb(1, 255, 255, 255));
	return (0);
}