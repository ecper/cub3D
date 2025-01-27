/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:08:23 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/27 21:41:18 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int		world_map[24][24] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 1, 1,
// 			1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 			0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 2, 2, 2,
// 			2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 2,
// 			0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0,
// 			0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1}, {1, 0, 0,
// 			0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1,
// 			0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0,
// 			1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 			0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 			0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 			0, 0, 0, 0, 0, 0, 1},
// 							{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 								0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0,
// 								0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 								{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 								0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0,
// 								0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 								1}, {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0,
// 								0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 4, 0, 4, 0,
// 								0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 								0, 0, 1}, {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0,
// 								0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 4, 0,
// 								4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 								0, 0, 0, 0, 1}, {1, 4, 0, 4, 4, 4, 4, 4, 4, 0,
// 								0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1,
// 								4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 								0, 0, 0, 0, 0, 0, 1}, {1, 4, 4, 4, 4, 4, 4, 4,
// 								4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 								1, 1, 1, 1, 1, 1, 1, 1}};

char		map[6][6] = {{'1', '1', '1', '1', '1', '1'}, {'1', '0', '0', '1',
			'0', '1'}, {'1', '0', '1', '0', '0', '1'}, {'1', '1', '0', '0', 'N',
			'1'}, {'1', '0', '0', '0', '0', '1'}, {'1', '1', '1', '1', '1',
			'1'}};

static void	init_player(void)
{
	t_player	*player;

	player = get_player();
	player->fov = M_PI / 4;
	player->angle = M_PI / 100;
	player->pos.x = 100;
	player->pos.y = 200;
	player->way.x = 0;
	player->way.y = 0;
}

static void	init_square(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			if (map[i][j] == '1')
				add_square(create_square(i * SQUARE_SIZE, j * SQUARE_SIZE));
			j++;
		}
		i++;
	}
}

void	init_t_data(void)
{
	t_data *data;
	t_player *player;
	// // void *img;
	// // char *relative_path = "./blue_stones.xpm";
	// // int img_width;
	// // int img_height;
	// double posX = 22, posY = 12;
	// double dirX = -5, dirY = -0.3;
	// double planeX = 0, planeY = 2;

	// double time = 0;
	// double oldTime = 0;
	init_player();
	init_square();
	player = get_player();
	data = get_t_data();
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, WINDOW_NAME);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);

	mlx_hook(data->win, ON_KEYDOWN, ON_KEYDOWN, key_event, data);
	mlx_hook(data->win, ON_KEYUP, ON_KEYUP, key_event, data);
	// mlx_key_hook(data->win, key_event, data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);

	// for (int x = 0; x < WIDTH; x++)
	// {
	// 	double cameraX = 2 * x / (double)WIDTH - 1;
	// 	double rayDirX = dirX + planeX * cameraX;
	// 	double rayDirY = dirY + planeY * cameraX;

	// 	int mapX = (int)posX;
	// 	int mapY = (int)posY;

	// 	double sideDistX;
	// 	double sideDistY;

	// 	double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
	// 	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
	// 	double perpWallDist;

	// 	int stepX;
	// 	int stepY;

	// 	int hit = 0;
	// 	int side;

	// 	if (rayDirX < 0)
	// 	{
	// 		stepX = -1;
	// 		sideDistX = (posX - mapX) * deltaDistX;
	// 	}
	// 	else
	// 	{
	// 		stepX = 1;
	// 		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	// 	}
	// 	if (rayDirY < 0)
	// 	{
	// 		stepY = -1;
	// 		sideDistY = (posY - mapY) * deltaDistY;
	// 	}
	// 	else
	// 	{
	// 		stepY = 1;
	// 		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	// 	}

	// 	while (hit == 0)
	// 	{
	// 		if (sideDistX < sideDistY)
	// 		{
	// 			sideDistX += deltaDistX;
	// 			mapX += stepX;
	// 			side = 0;
	// 		}
	// 		else
	// 		{
	// 			sideDistY += deltaDistY;
	// 			mapY += stepY;
	// 			side = 1;
	// 		}
	// 		if (world_map[mapX][mapY] > 0)
	// 			hit = 1;
	// 	}

	// 	if (side == 0)
	// 		perpWallDist = (sideDistX - deltaDistX);
	// 	else
	// 		perpWallDist = (sideDistY - deltaDistY);

	// 	int lineHeight = (int)(HEIGHT / perpWallDist);

	// 	int drawStart = -lineHeight / 2 + HEIGHT / 2;
	// 	if (drawStart < 0)
	// 		drawStart = 0;
	// 	int drawEnd = lineHeight / 2 + HEIGHT / 2;
	// 	if (drawEnd >= HEIGHT)
	// 		drawEnd = HEIGHT - 1;

	// 	// choose wall color
	// 	int color;
	// 	switch (world_map[mapX][mapY])
	// 	{
	// 	case 1:
	// 		color = create_trgb(1, 255, 0, 0);
	// 		break ; // red
	// 	case 2:
	// 		color = create_trgb(1, 0, 255, 0);
	// 		break ; // green
	// 	case 3:
	// 		color = create_trgb(1, 0, 0, 255);
	// 		break ; // blue
	// 	case 4:
	// 		color = create_trgb(1, 255, 255, 255);
	// 		break ; // white
	// 	default:
	// 		color = create_trgb(1, 255, 255, 0);
	// 		break ; // yellow
	// 	}
	// 	if (side == 1)
	// 		color = color / 2;

	// 	for (int i = drawStart; i < drawEnd; i++)
	// 	{
	// 		my_mlx_pixel_put(&data->img, x, i, color);
	// 		i++;
	// 	}
	// 	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	// }

	// img = mlx_xpm_file_to_image(data->mlx, relative_path, &img_width,
	// 		&img_height);
}