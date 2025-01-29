#include <../includes/cub3d.h>

void printmap(char **map){
	int i = 0;
	printf("--- printmap ---\n");
	while(map[i] !=NULL){
		printf("%s\n", map[i]);
		i++;
	}
	printf("--- printmap ---\n");

}

//example NO textures/wall_1.xpm
int	validation_path(t_config *config,char *line)
{
	char	*path;
	int		len;
	int		direction;
	int		fd;

	direction = is_texpath(line);
	line = line + 2;
	path = ft_trim_white(line);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{	
		print_error("Error:Only input texture path that must have .xpm");
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{	
		print_error("Error:Input correct texture path");
		close(fd);
		return (0);
	}
	close (fd);
	if (direction == NO && config->path_no.appear == false)
	{
		config->path_no.path = path;
		config->path_no.appear = true;
	}
	else if (direction == SO && config->path_so.appear == false)
	{
		config->path_so.path = path;
		config->path_so.appear = true;
	}
	else if (direction == WE && config->path_we.appear == false)
	{
		config->path_we.path = path;
		config->path_we.appear = true;
	}
	else if (direction == EA && config->path_ea.appear == false)
	{
		config->path_ea.path = path;
		config->path_ea.appear = true;
	}
	else
	{
		if(path)
		{	
			free(path);
			print_error("Error : identifier is one");
		}

	}
	return (1);
}

// example F 184,113,39
int	validation_color(t_config *config, char *line)
{
	int		color_place;
	char	*trim_line;
	char	**color_array;
	int		i;

	color_place = is_color(line);
	line ++;
	trim_line = ft_trim_white(line);
	color_array = ft_split(trim_line, ',');
	free(trim_line);
	if (!color_array)
		return (0);
	if (count_strarray(color_array) != 3)
	{
		wp_free(&color_array);
		print_error("Error : Enter only three colors R, G, B");
		return (0);
	}
	i = 0;
	if (color_place == FLOOR && config->floor.appear == false)
	{
		while (i < MAX_COLOR)
		{
			config->floor.color[i] = color_atoi(color_array[i]);
			if (config->floor.color[i] == ATOI_ERROR)
			{	
				wp_free(&color_array);
				print_error("Error : color range is from 0 to 255,only digit");
				return (0);
			}
			i++;
		}
		config->floor.appear = true;
	}
	else if (color_place == CEIL && config->ceil.appear == false)
	{
		while (i < MAX_COLOR)
		{
			config->ceil.color[i] = color_atoi(color_array[i]);
			if (config->ceil.color[i] == ATOI_ERROR)
			{	
				wp_free(&color_array);
				print_error("Error : color range is from 0 to 255");
				return (0);
			}
			i++;
		}
		config->ceil.appear = true;
	}
	else
	{
		print_error("Error : identifier is one");
		wp_free(&color_array);
		exit(1);
	}
	wp_free(&color_array);
	return (1);
}

int parsing_line(t_config *config, char *line, int line_id)
{
	if (line_id == LINE_PATH)
		return (validation_path(config, line));
	else if (line_id == LINE_COLOR)
		return (validation_color(config, line));
	// else if(line_id == LINE_MAP)
	// 	return (validation_map(config,line));
	else
		return (0);
}

int	check_map_emptyline(char **map, int i)
{
	while (map[i] != NULL)
	{
		if (is_emptyline(map[i]))
		{
			print_error("Error:Map information must not contain blank lines");
			return (1);
		}
		i ++;
	}
	return (0);
}

int	check_map_char(char **map, int i)
{
	int	j;

	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] !='\0')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W'
				&& map[i][j] != 'E' && map[i][j] != '\n')
			{
				print_error("Error:invalid character");
				return (1);
			}
			j ++;
		}
		i ++;
	}
	return (0);
}

int	check_map_start(t_config *config, char **map , int i)
{
	int	j;

	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				if (config->p_count == 0)
				{
					config->p_count++;
					config->x_position = j;
					config->y_position = i;
					config->p_direction = map[i][j];
				}
				else
					return (print_error("Error:start position is one"), 1);
			}
			j ++;
		}
		i ++;
	}
	return (0);
}

char	**make_game_map(t_map *config_file)
{
	char	**map;
	int		array_size;
	int		i;
	int		start;

	array_size = (config_file->height - config_file->map_h);
	map = ft_calloc(sizeof(char *), array_size +1);
	i = 0;
	start = config_file ->map_h;
	while (i < array_size)
		map[i++] = ft_strdup(config_file->mapinfo[start ++]);
	map[i] = NULL;
	return(map);
}

int	get_maxarray_index(char **stringarray)
{
	int	i;
	int	len;
	int	max_len;

	i = 0;
	max_len = 0;
	while(stringarray[i] != NULL)
	{
		len = ft_strlen(stringarray[i ++]);
		if(len > max_len)
			max_len = len;
	}
	return (max_len);
}

void	map_strcpy(char *dst, const char *src)
{
	size_t	i;
	size_t	len;

	len = ft_strlen((char *)src);
	i = 0;
	if (dst == NULL || src == NULL)
		return (len);
	while (src[i] != '\0')
	{
		if(src[i] == '\n')
			dst[i] = '2';
		else
			dst[i] = src[i];
		i++;
	}
	return (len);
}

char	**make_validation_map(char **map)
{
	int		max_len;
	int		num_array;
	int		i;
	char	**v_map;

	max_len = get_maxarray_index(map);
	num_array = count_strarray(map);
	printf("len = %d,array_size = %d\n",max_len,num_array);
	v_map = ft_calloc(sizeof(char *), (num_array +1));
	i = 0;
	while (i < num_array)
	{
		v_map[i] = ft_calloc(sizeof(char), (max_len + 1));
		ft_memset(v_map[i], '3', max_len);
		v_map[i][max_len] = '\0';
		map_strcpy(v_map[i], map[i]);
		i ++;
	}
	v_map [i] = NULL;
	wp_free(&map);
	printf("validation map is\n");
	printmap(v_map);
	return (v_map);
}

int	check_horizon(char **map, int x, int y)
{
	int	i;

	i = 0;
	while (i <= x)
	{
		if (map[0][i] == '0' || map[0][i] == 'N' || map[0][i] == 'S'
		|| map[0][i] == 'W' || map[0][i] == 'E')
			return (1);
		if (map[y][i] == '0' || map[y][i] == 'N' || map[y][i] == 'S'
		|| map[y][i] == 'W' || map[y][i] == 'E')
			return (1);
		i++;
	}
	return (0);
}

int check_verticall(char **map,int x,int y)
{
	int	i;

	i = 0;
	while (i < y)
	{
		if (map[i][0] == '0' || map[i][0] == 'N' || map[i][0] == 'S'
		|| map[i][0] == 'W' || map[i][0] == 'E')
			return (1);
		if (map[i][x] == '0' || map[i][x] == 'N' || map[i][x] == 'S'
		|| map[i][x] == 'W' || map[i][x] == 'E')
			return (1);
		i ++;
	}
	return (0);
}

int	see_aroundchar(char **map, int point_x,int point_y)
{
	if (map[point_y + 1][point_x] == ' ' || map[point_y + 1][point_x] == '2'
		||map[point_y + 1][point_x] == '3')
		return (1);
	else if (map[point_y -1][point_x] == ' ' || map[point_y -1][point_x] == '2'
		||map[point_y - 1][point_x] == '3')
		return (1);
	else if (map[point_y][point_x +1] == ' ' || map[point_y][point_x +1] == '2'
		||map[point_y][point_x +1] == '3')
		return (1);
	else if (map[point_y][point_x -1] == ' ' || map[point_y][point_x -1] == '2'
		||map[point_y][point_x -1] == '3')
		return (1);
	else
		return (0);
}

int	check_inter(char **map, int x,int y)
{
	int		i;
	int		j;

	i = 1;
	while (i < y)
	{
		j = 1;
		while (j < x)
		{
			if ((map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				&& see_aroundchar(map, j, i))
				{
					printf("error y=%d ,x = %d\n",i,j);
					fflush(0);
					return (1);
				}
			j++;
		}
		i++;
	}
	return (0);
}

void check_surroundwall(char **map)
{
	int		x;
	int		y;

	x = get_maxarray_index(map) -1;
	y = count_strarray(map) - 1;
	if (check_horizon(map, x, y) || check_verticall(map, x, y)
		||check_inter(map, x, y))
		print_error("Error : the map must be surrounded by walls");
	// printf("return value %d",check_horizon(map, x, y));
	// printf("return value %d",check_verticall(map, x, y));
	// printf("return value %d",check_inter(map, x, y));

}

void	validation_map(t_config *config, t_map *config_file, int i)
{
	char	**dup_map;
	char	**v_map;

	if (check_map_emptyline(config_file->mapinfo, i)
		|| check_map_char(config_file->mapinfo, i)
		|| check_map_start(config, config_file->mapinfo, i))
	{
		wp_free(&(config_file->mapinfo));
		free(config_file);
		free(config);
	}
	config->y_position = config->y_position - config_file->map_h;
	config->map.mapinfo = make_game_map(config_file);
	dup_map = make_game_map(config_file);
	v_map = make_validation_map(dup_map);
	check_surroundwall(v_map);
	wp_free(&v_map);

}
t_config	*parser(int fd)
{
	t_map		*config_file;
	t_config	*config;
	int			i;
	int			line_id;

	config_file = read_configfile(fd);
	if (!config_file)
		return (NULL);
	
	//↑ここまででファイルの読み込みが成功、leak無し↓test
	// int i = 0;
	// while (con_file->mapinfo[i])
	// {
	// 	printf("%s",con_file->mapinfo[i++]);
	// }
	// printf("\nheightis%d\n",con_file->height);
	// wp_free(&(con_file->mapinfo));
	// free(&con_file);
	//test
	config = ft_calloc(sizeof(t_config), 1);
	if (!config)
		return (NULL);
	//一行ずつずつ読み込む、読み込んだら種類を判断してconfigのメンバに格納する
	i = 0;
	//con_fileのmapinfoの０から順に読み込む
	while (i < config_file->height)
	{
		//まず、ラインの種類を判断する。
		line_id = judge_line(config_file->mapinfo[i]);
		if(check_mapinfo_last(config,line_id))
			print_error("Enter only the necessary information and map information last.\n"),exit(1);
		//ラインの種類に応じたparserに通す。
		if(line_id!=LINE_EMPTY)
			if(!(parsing_line(config,config_file->mapinfo[i],line_id)))
				exit(1);
		// printf("line type[%d] is %s",line_id,config_file->mapinfo[i]);
		printf("\nconfin-check\n");
		printf("config,path-no = %s:apper %d\n",config->path_no.path,config->path_no.appear);
		printf("config,path-so = %s:apper %d\n",config->path_so.path,config->path_so.appear);
		printf("config,path-we = %s:apper %d\n",config->path_we.path,config->path_we.appear);
		printf("config,path-ea = %s:apper %d\n",config->path_ea.path,config->path_ea.appear);
		printf("config,floor : color[R] = %d color[G] = %d color[B] = %d : apper %d\n",config->floor.color[0],config->floor.color[1],config->floor.color[2],config->floor.appear);
		printf("config,ceil : color[R] = %d color[G] = %d color[B] = %d : apper %d\n",config->ceil.color[0],config->ceil.color[1],config->ceil.color[2],config->ceil.appear);
		i++;
		if(present_info(config))
			break;
	}
	while (is_emptyline(config_file->mapinfo[i]))
		i++;
	config_file->map_h = i;
	validation_map(config, config_file, i);
	wp_free(&(config_file->mapinfo));
	free(config_file);
	printf("\ndirection is %c\n",config->p_direction);
	printf("start position[%d][%d] \n",config->y_position, config->x_position);
	return (config);
}
