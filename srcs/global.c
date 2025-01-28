/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:06:52 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/28 16:28:39 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*get_t_data(void)
{
	static t_data	data;

	return (&data);
}

t_player	*get_player(void)
{
	static t_player	player;

	return (&player);
}

t_square	**get_square(void)
{
	static t_square	*square;

	return (&square);
}

t_texture_img	*get_texture_img(void)
{
	static t_texture_img texture_img[4];

	return (texture_img);
}
