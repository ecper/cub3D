/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:08:23 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/31 23:16:53 by hauchida         ###   ########.fr       */
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

// initialisation functions
char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000200000001";
	map[4] = "100000000000001";
	map[5] = "100000030000001";
	map[6] = "100001000000001";
	map[7] = "100000040000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

static void	init_player(void)
{
	t_player	*player;

	player = get_player();
	player->fov = M_PI / 4;
	player->angle = 0;
	player->pos.x = 4;
	player->pos.y = 4;
}

void	init_t_data(void)
{
	t_data		*data;
	t_player	*player;

	init_player();
	player = get_player();
	data = get_t_data();
	data->map = get_map();
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, WINDOW_NAME);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	mlx_hook(data->win, ON_KEYDOWN, ON_KEYDOWN, key_event, data);
	mlx_hook(data->win, ON_KEYUP, ON_KEYUP, key_event, data);
	mlx_loop_hook(data->mlx, render, data);
	init_texture_img(NORTH, "./textures/blue_stones.xpm");
	init_texture_img(WEST, "./textures/eagle.xpm");
	init_texture_img(SOUTH, "./textures/greystone.xpm");
	init_texture_img(EAST, "./textures/red.xpm");
	mlx_loop(data->mlx);
}
