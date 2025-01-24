/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:21:31 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/24 17:47:40 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free_t_data();
	exit(0);
	return (0);
}

static void	change_player_pos(double dx, double dy)
{
	t_player	*player;

	player = get_player();
	player->pos.x += dx;
	player->pos.y += dy;
	player->way.x += dx;
	player->way.y += dy;
}

static void	move(int keycode)
{
	t_player	*player;

	player = get_player();
	if (keycode == LEFT_ARROW_KEY)
		player->is_left_angle = 1;
	else if (keycode == RIGHT_ARROW_KEY)
		player->is_right_angle = 1;
	else if (keycode == TOP_ARROW_KEY)
		printf("TOP_ARROW_KEY PRESSED");
	else if (keycode == DOWN_ARROW_KEY)
		printf("DOWN_ARROW_KEY PRESSED");
}

int	key_event(int keycode, t_data *data)
{
	t_player *player;

	player = get_player();
	if (keycode == ESC_KEY)
		close_window(data);
	else if (keycode == W_KEY)
		change_player_pos(0, -1);
	else if (keycode == A_KEY)
		change_player_pos(-1, 0);
	else if (keycode == S_KEY)
		change_player_pos(0, 1);
	else if (keycode == D_KEY)
		change_player_pos(1, 0);
	else if (keycode == LEFT_ARROW_KEY || keycode == RIGHT_ARROW_KEY
		|| keycode == TOP_ARROW_KEY || keycode == DOWN_ARROW_KEY)
		move(keycode);
	return (0);
}