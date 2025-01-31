/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:04:21 by hauchida          #+#    #+#             */
/*   Updated: 2025/02/01 01:02:11 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 640
# define HEIGHT 480
# define WINDOW_NAME "WE ARE THE WORLD"

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define SQUARE_SIZE 64

# define ON_KEYDOWN 2
# define ON_KEYUP 3

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
	char		**map;
}				t_data;

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_player_ray
{
	double		raydir_x;
	double		raydir_y;
	double		ray_x;
	double		ray_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		dist_x;
	double		dist_y;
	double		step_x;
	double		step_y;
	double		perp_wall_dist;
	int			line_height;
	int			start_y;
	int			end_y;
	int			side;
}				t_player_ray;

typedef struct s_tex_calc
{
	int			tex_x;
	int			tex_y;
	double		tex_pos;
	double		step;
}				t_tex_calc;

// typedef struct s_ray
// {
// 	t_vector		pos;
// 	t_vector		way;
// }					t_ray;

typedef struct s_player
{
	double		fov;
	t_vector	pos;
	// t_vector		way;
	// t_vector		plane;
	double		angle;
	int			is_right_angle;
	int			is_left_angle;
}				t_player;

typedef struct s_texture_img

{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_texture_img;

// parse
int				open_cubfile(int argc, char *filename);

// global.c
t_data			*get_t_data(void);
t_player		*get_player(void);
t_texture_img	*get_texture_img(void);

// init.c
void			init_t_data(void);

// free.c
void			free_t_data(void);

// event.c
int				key_event(int keycode, t_data *data);

// utils.c
void			my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
unsigned int	get_texture_pixel_color(t_texture_img texture_img, int x,
					int y);
int				create_trgb(int t, int r, int g, int b);
double			ft_min(double c1, double c2);
double			ft_max(double c1, double c2);

// vector.c
t_vector		vector_add(t_vector a, t_vector b);
t_vector		vector_sub(t_vector a, t_vector b);
double			vector_mag(t_vector a);

// texture.c
void			draw_texture(t_player_ray player_ray, int i);

// raycastinc.c
void			init_player_ray(t_player_ray *player_ray, int map_x, int map_y,
					double start_x);
void			calc_player_ray(t_player_ray *player_ray, int map_x, int map_y,
					double start_x);
// render.c
int				render(t_data *data);

// draw.c
void			draw(void);

// error.c
int				open_ber_file(int argc, char *filename);

// square.c
// t_square			*create_square(int x, int y);
// void				add_square(t_square *new);

#endif