/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:21:31 by hauchida          #+#    #+#             */
/*   Updated: 2025/02/01 06:55:53 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	t_config	**config;

	config = get_config();
	free_texture_image();
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free_t_data();
	all_free(*config, NULL);
	exit(0);
	return (0);
}

static void	change_player_pos(double dx, double dy)
{
	t_data		*data;
	t_player	*player;
	t_config	**config;

	data = get_t_data();
	player = get_player();
	config = get_config();
	if (data->map[(int)(player->pos.y + dy)][(int)(player->pos.x + dx)] > '0'
		&& data->map[(int)(player->pos.y + dy)][(int)(player->pos.x
			+ dx)] != (*config)->p_direction)
		return ;
	player->pos.x += dx;
	player->pos.y += dy;
}

static void	move(int keycode)
{
	t_player	*player;
	double		angle_speed;

	player = get_player();
	angle_speed = 0.03;
	if (keycode == LEFT_ARROW_KEY)
		player->angle -= angle_speed;
	else if (keycode == RIGHT_ARROW_KEY)
		player->angle += angle_speed;
	else if (keycode == TOP_ARROW_KEY)
		printf("TOP_ARROW_KEY PRESSED");
	else if (keycode == DOWN_ARROW_KEY)
		printf("DOWN_ARROW_KEY PRESSED");
	if (player->angle > 2 * M_PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * M_PI;
}

int	key_event(int keycode, t_data *data)
{
	double		cos_angle;
	double		sin_angle;
	t_player	*player;

	player = get_player();
	cos_angle = cos(player->angle) * 0.03;
	sin_angle = sin(player->angle) * 0.03;
	if (keycode == ESC_KEY)
		close_window(data);
	else if (keycode == W_KEY)
		change_player_pos(cos_angle, sin_angle);
	else if (keycode == A_KEY)
		change_player_pos(sin_angle, -cos_angle);
	else if (keycode == S_KEY)
		change_player_pos(-cos_angle, -sin_angle);
	else if (keycode == D_KEY)
		change_player_pos(-sin_angle, cos_angle);
	else if (keycode == LEFT_ARROW_KEY || keycode == RIGHT_ARROW_KEY
		|| keycode == TOP_ARROW_KEY || keycode == DOWN_ARROW_KEY)
		move(keycode);
	return (0);
}
