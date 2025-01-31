/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:04:21 by hauchida          #+#    #+#             */
/*   Updated: 2025/02/01 00:51:57 by soaoki           ###   ########.fr       */
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
# include <stdbool.h>
# include <fcntl.h>
# include <../Libft/libft.h>
# include <../get_next_line/get_next_line.h>

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

//color config
# define FLOOR 1
# define CEIL 2

//atoi
# define ATOI_ERROR 256

enum						e_line_type
{
	LINE_EMPTY,
	LINE_PATH,
	LINE_COLOR,
	LINE_MAP,
};
typedef enum e_token_type	t_line_type;

enum						e_direction
{
	NO = 1,
	SO = 2,
	WE = 3,
	EA = 4,
};
typedef enum e_direction	t_direction;

enum						e_color
{
	RED,
	GLEEN,
	BLUE,
	MAX_COLOR,
};
typedef enum e_color		t_color;

//textureのパスと現れたかを確認する
typedef struct s_tex
{
	char	*path;
	bool	appear;
}t_tex;

typedef struct s_area
{
	int		color[MAX_COLOR];
	bool	appear;
}t_area;

typedef struct s_map
{
	char	**mapinfo;
	int		map_h;
	int		max_len;
	int		height;
}t_map;

//parse用の構造体
typedef struct s_config
{
	t_tex	path_no;
	t_tex	path_so;
	t_tex	path_we;
	t_tex	path_ea;
	t_area	floor;
	t_area	ceil;
	t_map	map;
	char	p_direction;
	int		p_count;
	int		x_position;
	int		y_position;
}t_config;

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
	double		fov;
	t_vector	pos;
	t_vector	way;
	double		angle;
	int			is_right_angle;
	int			is_left_angle;
}				t_player;

// global.c
t_data			*get_t_data(void);
t_player		*get_player(void);

// init.c
void			init_t_data(void);

// free.c
void			free_t_data(void);

// event.c
int				key_event(int keycode, t_data *data);

// utils.c
void			my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
int				create_trgb(int t, int r, int g, int b);
int				ft_min(double c1, double c2);
int				ft_max(double c1, double c2);

// vector.c
t_vector		vector_add(t_vector a, t_vector b);
t_vector		vector_sub(t_vector a, t_vector b);
double			vector_mag(t_vector a);

// ray.c
t_ray			with2p(t_vector begin, t_vector end);
t_vector		ray_begin(t_ray ray);
t_vector		ray_end(t_ray ray);
t_vector		*calc_intersection(t_ray ray1, t_ray ray2);

// render.c
int				render(t_data *data);

//error.c
void			print_error(char *msg);
void			wp_free(char ***str);
void			free_configfile(t_map *config_file);
void			free_config(t_config *config);
void			all_free(t_config *config, t_map *config_file);
void			free_exit(t_config *config, t_map *config_file);

//readfile.c
t_map			*read_configfile(int fd);

//parser.c
t_config		*parser(int fd);
int				parsing_line(t_config *config, char *line, int line_id);

//parser_path.c
int				validation_path(t_config *config, char *line);

//parser_color.c
int				count_char(const char *str, char target);
int				validation_color(t_config *config, char *line);
char			**check_numarray(char *line);
int				set_color(t_config *config, char **color_array,
					int color_place);

//parser_util.c
char			*ft_trim_white(const char *str);
int				color_atoi(char *color_code);
int				count_strarray(char **str);
int				present_info(t_config *config);
int				get_maxarray_index(char **stringarray);

//line_util.c
int				is_emptyline(char *line);
int				is_texpath(char *line);
int				is_color(char *line);
int				judge_line(char *line);
void				check_mapinfo_last(t_config *config, t_map *config_file, int line_id);

//map.c
int				check_map_emptyline(char **map, int i);
int				check_map_char(char **map, int i);
int				check_map_start(t_config *config, char **map, int i);
void			validation_map(t_config *config, t_map *config_file, int i);

//map_util.c
char			**make_game_map(t_map *config_file);
void			map_strcpy(char *dst, const char *src);
char			**make_validation_map(char **map);

//map_surround.c
int				check_horizon(char **map, int x, int y);
int				check_verticall(char **map, int x, int y);
int				see_aroundchar(char **map, int point_x, int point_y);
int				check_inter(char **map, int x, int y);
int				check_surroundwall(char **map);

#endif