/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:25:44 by hauchida          #+#    #+#             */
/*   Updated: 2025/02/01 06:58:17 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture_image(void)
{
	t_data			*data;
	t_texture_img	*texture_img;

	texture_img = get_texture_img();
	data = get_t_data();
	if (texture_img[NORTH].img)
		mlx_destroy_image(data->mlx, texture_img[NORTH].img);
	if (texture_img[SOUTH].img)
		mlx_destroy_image(data->mlx, texture_img[SOUTH].img);
	if (texture_img[EAST].img)
		mlx_destroy_image(data->mlx, texture_img[EAST].img);
	if (texture_img[WEST].img)
		mlx_destroy_image(data->mlx, texture_img[WEST].img);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
}

void	free_t_data(void)
{
	t_data	*data;

	data = get_t_data();
	if (data->mlx)
		free(data->mlx);
}
