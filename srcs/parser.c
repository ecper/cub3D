#include <../includes/cub3d.h>

// typedef struct s_tex
// {
//     char *path;
//     bool appear;
// }t_tex;

// typedef struct s_color
// {
//     int red;
//     int green;
//     int blue;
// }t_color;

// typedef struct s_map
// {
// 	char	**mapinfo;
// 	int		width;
// 	int		height;
// }t_map;

// typedef struct s_config
// {
// 	t_tex   path_NO;
//     t_tex   path_SO;
//     t_tex   path_WE;
//     t_tex   path_EA;
//     t_color floor;
//     t_color ceil;
//     t_map    map;
// }t_config;

static int	add_line(t_map *map, char *line)
{
	char	**tmp;
	int		i;

	if (!line)
		return (0);
	map->height++;
	tmp = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!tmp)
	{
		free(line);
		return (0);
	}
	tmp[map->height] = NULL;
	i = 0;
	while (i < map->height - 1)
	{
		tmp[i] = ft_strdup(map->mapinfo[i]);
		i++;
	}
	tmp[i] = line;
	if (map->mapinfo)
		wp_free(&(map->mapinfo));
	map->mapinfo = tmp;
	return (1);
}

t_map *read_configfile(int fd)
{
	t_map *buff;
	char *readline;

	buff=ft_calloc(sizeof(t_map),1);
	if(!buff)
		return (NULL);
	readline = get_next_line(fd);
	while (readline != NULL)
	{
		if (!add_line(buff, readline))
		{
			free(readline);
			close(fd);
			return (0);
		}
		readline = get_next_line(fd);
	}
	close(fd);
	if (!buff || !(buff->mapinfo))
		print_error("Error\n Could not load map");
	return (buff);
}

t_config	*parser(int fd)
{
	t_config	*config;
	t_map		*con_file;

	con_file = read_configfile(fd);
	if (!con_file)
		return (NULL);
	
	//test
	int i = 0;
	while (con_file->mapinfo[i])
	{
		printf("%s",con_file->mapinfo[i++]);
	}
	printf("\nheightis%d\n",con_file->height);
	wp_free(&(con_file->mapinfo));
	free(&con_file);
	//test
	// config = ft_calloc(sizeof(t_config), 1);
	if (!config)
		return (NULL);

	//一行ずつずつ読み込む、読み込んだら種類を判断してconfigのメンバに格納する
	return (config);
}
