/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:04:21 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/22 19:11:44 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 640
# define HEIGHT 480
# define WINDOW_NAME "WE ARE THE WORLD"

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_ARROW_KEY 65361
# define TOP_ARROW_KEY 65362
# define RIGHT_ARROW_KEY 65363
# define DOWN_ARROW_KEY 65364
# define ESC_KEY 65307

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img_data	img;
}				t_data;

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_ray
{
	t_vector	pos;
	t_vector	way;
}				t_ray;

typedef struct s_player
{
	t_vector	vector;
	double		angle;
}				t_player;

// typedef struct s_ray
// {
// 	double		side_dist_x;
// 	double		side_dist_y;
// 	double		delta_dist_x;
// 	double		delta_dist_y;
// }				t_ray;

// global.c
t_data			*get_t_data(void);

// init.c
void			init_t_data(void);

// free.c
void			free_t_data(void);

// event.c
int				key_event(int keycode, t_data *data);

// utils.c
void			my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
int				create_trgb(int t, int r, int g, int b);

// vector.c
void			vector_plus(t_vector *result, t_vector a, t_vector b);
void			vector_minus(t_vector *result, t_vector a, t_vector b);

#endif