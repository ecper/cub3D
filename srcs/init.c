/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:08:23 by hauchida          #+#    #+#             */
/*   Updated: 2025/02/01 02:11:29 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture_img(int dir, char *path)
{
	t_texture_img	*texture_img;
	t_data			*data;

	data = get_t_data();
	texture_img = get_texture_img();
	texture_img[dir].img = mlx_xpm_file_to_image(data->mlx, path,
			&(texture_img[dir].width), &(texture_img[dir].height));
	// TODO エラーハンドリング書く（exit_freeのイメージ)
	if (!(texture_img)[dir].img)
		return ;
	(texture_img)[dir].addr = mlx_get_data_addr((texture_img)[dir].img,
			&(texture_img)[dir].bits_per_pixel, &(texture_img)[dir].line_length,
			&(texture_img)[dir].endian);
}

static void	init_player(int map_x, int map_y, char p_direction)
{
	t_player	*player;

	player = get_player();
	player->fov = M_PI / 4;
	if (p_direction == 'N')
		player->angle = 3 * M_PI / 2;
	else if (p_direction == 'W')
		player->angle = M_PI;
	else if (p_direction == 'S')
		player->angle = M_PI / 2;
	else
		player->angle = 0;
	player->pos.x = map_x;
	player->pos.y = map_y;
}

static void	init_config_to_data(t_config *config)
{
	t_data	*data;

	data = get_t_data();
	data->map = (config)->map.mapinfo;
	data->ceil_color[0] = (config)->ceil.color[0];
	data->ceil_color[1] = (config)->ceil.color[1];
	data->ceil_color[2] = (config)->ceil.color[2];
	data->floor_color[0] = (config)->floor.color[0];
	data->floor_color[1] = (config)->floor.color[1];
	data->floor_color[2] = (config)->floor.color[2];
}

static void	init_texture(t_config *config)
{
	init_texture_img(NORTH, config->path_no.path);
	init_texture_img(WEST, config->path_we.path);
	init_texture_img(SOUTH, config->path_so.path);
	init_texture_img(EAST, config->path_ea.path);
}

void	init_t_data(void)
{
	t_data		*data;
	t_player	*player;
	t_config	**config;

	config = get_config();
	init_player((*config)->x_position, (*config)->y_position,
		(*config)->p_direction);
	player = get_player();
	data = get_t_data();
	data->mlx = mlx_init();
	if (!data->mlx)
		free_exit((*config), NULL);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, WINDOW_NAME);
	if (!data->win)
		free_exit((*config), NULL);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	mlx_hook(data->win, ON_KEYDOWN, ON_KEYDOWN, key_event, data);
	mlx_hook(data->win, ON_KEYUP, ON_KEYUP, key_event, data);
	mlx_loop_hook(data->mlx, render, data);
	init_config_to_data(*config);
	init_texture(*config);
	mlx_loop(data->mlx);
}
