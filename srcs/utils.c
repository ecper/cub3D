/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:20:14 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/28 16:35:15 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_min(double c1, double c2)
{
	if (c1 < c2)
		return (c1);
	else
		return (c2);
}

double	ft_max(double c1, double c2)
{
	if (c1 < c2)
		return (c2);
	else
		return (c1);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned int	get_texture_pixel_color(t_texture_img texture_img, int x, int y)
{
	char	*dst;

	dst = texture_img.addr + (y * texture_img.line_length + x
			* (texture_img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}
