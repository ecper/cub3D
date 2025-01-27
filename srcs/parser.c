#include <../includes/cub3d.h>

char	*ft_trim_white(const char *str)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] && (str[start] == ' ' || str[start] == '\n' || str[start] == '\t'))
			start++;

	while (end > start && (str[end] == ' ' || str[end] == '\n' || str[end] == '\t'))
		end--;
	return (ft_substr(str, start, end - start + 1));
}

int	color_atoi(const char *str)
{
	unsigned int	result;
	int				minus_flag;
	int				i;

	result = 0;
	minus_flag = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\r') || (str[i] == '\v') || (str[i] == '\f'))
		str++;
	i++;
	if (*str == '-')
	{
		minus_flag = 1;
		return (ATOI_ERROR);
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{	
		result = result * 10 + (*str++ - '0');
		if (0 > result || result > 255)
			return (ATOI_ERROR);
	}
	return ((int)result);
}

int	is_emptyline(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n' || line[0] == '\t')
		return (1);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	is_texpath(char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (EA);
	return (0);
}

int	is_color(char *line)
{
	if (line[0] == 'F')
		return (FLOOR);
	else if (line[0] == 'C')
		return (CEIL);
	return (0);
}

int	judge_line(char *line)
{
	if (is_emptyline(line))
		return (LINE_EMPTY);
	else if (is_texpath(line))
		return (LINE_PATH);
	else if (is_color(line))
		return (LINE_COLOR);
	else
		return (LINE_MAP);
}

int	check_mapinfo_last(t_config *config, int line_id)
{
	if (line_id == LINE_MAP)
	{
		if(config->ceil.appear && config->floor.appear && config->path_ea.appear && config->path_no.appear
		&& config->path_so.appear && config->path_we.appear)
			return (0);
		else
			return (1);
	}
	else
		return (0);
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
int count_strarray(char **str)
{
	int	i;

	i = 0;
	while (str[i]!=NULL)
		i++;
	return (i);
}

// example F 184,113,39
int validation_color(t_config *config,char *line)
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
	if (color_place == FLOOR && config->floor.appear ==false)
	{
		while (i < MAX_COLOR)
		{
			config->floor.color[i] = color_atoi(color_array[i]);
			if (config->floor.color[i] == ATOI_ERROR)
			{	
				wp_free(&color_array);
				print_error("Error : color range is from 0 to 255");
				return (0);
			}
			i++;
		}
		config->floor.appear = true;
	}
	else if (color_place == CEIL && config->ceil.appear ==false)
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

int present_info(t_config *config)
{
	if (config->ceil.appear && config->floor.appear && config->path_ea.appear
		&&config->path_no.appear && config->path_so.appear
		&& config->path_we.appear)
		return (1);
	return (0);
}

int parsing_line(t_config *config,char *line,int line_id)
{
	if(line_id == LINE_PATH)
		return (validation_path(config,line));
	else if(line_id == LINE_COLOR)
		return (validation_color(config,line));
	// else if(line_id == LINE_MAP)
	// 	return (validation_map(config,line));
	else
		return (0);
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
	// validation_map(config,config_file,i);
	wp_free(&(config_file->mapinfo));
	free(&config_file);
	return (config);
}
