/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:20:14 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/24 15:08:15 by hauchida         ###   ########.fr       */
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
