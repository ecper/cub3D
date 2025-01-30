/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:08:23 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/31 05:30:06 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture_img(void)
{
	t_texture_img	*texture_img;
	t_data			*data;

	data = get_t_data();
	texture_img = get_texture_img();
	texture_img[NORTH].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/eagle.xpm", &(texture_img[NORTH].width),
			&(texture_img[NORTH].height));
	// TODO エラーハンドリング書く（exit_freeのイメージ)
	if (!(texture_img)[NORTH].img)
		return ;
	(texture_img)[NORTH].addr = mlx_get_data_addr((texture_img)[NORTH].img,
			&(texture_img)[NORTH].bits_per_pixel,
			&(texture_img)[NORTH].line_length, &(texture_img)[NORTH].endian);
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
	// TODO change way by args (for example N, S, W, E)
	// player->way.x = player_pos_x * 3;
	// player->way.y = (player_pos_y / 2) * 3;
}

// static void	init_square(void)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (i < 6)
// 	{
// 		j = 0;
// 		while (j < 6)
// 		{
// 			if (map[i][j] == '1')
// 				add_square(create_square(i * SQUARE_SIZE, j * SQUARE_SIZE));
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	init_t_data(void)
{
	t_data		*data;
	t_player	*player;

	init_player();
	// init_square();
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
	init_texture_img();
	mlx_loop(data->mlx);
}
