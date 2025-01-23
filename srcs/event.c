/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:21:31 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/23 16:15:48 by hauchida         ###   ########.fr       */
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
static void	move(int keycode)
{
	t_player *player;

	player = get_player();
	if (keycode == LEFT_ARROW_KEY)
		player->angle += M_PI / 60;
	else if (keycode == RIGHT_ARROW_KEY)
		player->angle -= M_PI / 60;
	else if (keycode == TOP_ARROW_KEY)
		printf("TOP_ARROW_KEY PRESSED");
	else if (keycode == DOWN_ARROW_KEY)
		printf("DOWN_ARROW_KEY PRESSED");
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		close_window(data);
	else if (keycode == W_KEY)
		printf("W KEY PRESSED");
	else if (keycode == A_KEY)
		printf("A KEY PRESSED");
	else if (keycode == S_KEY)
		printf("S KEY PRESSED");
	else if (keycode == LEFT_ARROW_KEY || keycode == RIGHT_ARROW_KEY
		|| keycode == TOP_ARROW_KEY || keycode == DOWN_ARROW_KEY)
		move(keycode);
	return (0);
}