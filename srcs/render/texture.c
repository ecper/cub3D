/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:48:27 by hauchida          #+#    #+#             */
/*   Updated: 2025/02/01 09:07:55 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_texture_dir(double raydir_x, double raydir_y, int side)
{
	if (raydir_y >= 0 && ((raydir_x >= 0 || raydir_x <= 0)) && side == 1)
		return (SOUTH);
	else if (raydir_x >= 0 && (raydir_y >= 0 || raydir_y <= 0) && side == 0)
		return (EAST);
	else if (raydir_x <= 0 && (raydir_y <= 0 || raydir_y >= 0) && side == 0)
		return (WEST);
	else
		return (NORTH);
}

static void	calc_texture_pixel_pos(t_tex_calc *tex_calc,
		t_texture_img *texture_img, t_player_ray player_ray, int texture_dir)
{
	t_player	*player;
	double		wall_x;

	player = get_player();
	tex_calc->step = 1.0 * texture_img[texture_dir].height
		/ player_ray.line_height;
	if (player_ray.side == 0)
		wall_x = (player->pos.y) + player_ray.perp_wall_dist
			* (player_ray.raydir_y);
	else
		wall_x = (player->pos.x) + player_ray.perp_wall_dist
			* (player_ray.raydir_x);
	wall_x -= floor((wall_x));
	tex_calc->tex_x = (int)(wall_x * (double)texture_img[texture_dir].width);
	if (player_ray.side == 0 && player_ray.raydir_x > 0)
		tex_calc->tex_x = texture_img[texture_dir].width - tex_calc->tex_x - 1;
	if (player_ray.side == 1 && player_ray.raydir_y < 0)
		tex_calc->tex_x = texture_img[texture_dir].width - tex_calc->tex_x - 1;
	tex_calc->tex_pos = (player_ray.start_y - (HEIGHT / 2)
			+ (player_ray.line_height / 2)) * tex_calc->step;
}

void	draw_texture(t_player_ray player_ray, int i)
{
	t_data			*data;
	t_texture_img	*texture_img;
	t_tex_calc		tex_calc;
	double			wall_x;
	int				texture_dir;

	texture_img = get_texture_img();
	data = get_t_data();
	texture_dir = check_texture_dir(player_ray.raydir_x, player_ray.raydir_y,
			player_ray.side);
	calc_texture_pixel_pos(&tex_calc, texture_img, player_ray, texture_dir);
	while (player_ray.start_y < player_ray.end_y)
	{
		tex_calc.tex_y = (int)tex_calc.tex_pos
				& (texture_img[texture_dir].height - 1);
		tex_calc.tex_pos += tex_calc.step;
		my_mlx_pixel_put(&data->img, i, player_ray.start_y,
			get_texture_pixel_color(texture_img[texture_dir], tex_calc.tex_x,
				tex_calc.tex_y));
		player_ray.start_y++;
	}
}
