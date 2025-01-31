/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:01:30 by soaoki            #+#    #+#             */
/*   Updated: 2025/02/01 00:46:43 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	parsing_line(t_config *config, char *line, int line_id)
{
	if (line_id == LINE_PATH)
		return (validation_path(config, line));
	else if (line_id == LINE_COLOR)
		return (validation_color(config, line));
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
	config = ft_calloc(sizeof(t_config), 1);
	if (!config)
		return (NULL);
	i = 0;
	while (i < config_file->height)
	{
		line_id = judge_line(config_file->mapinfo[i]);
		check_mapinfo_last(config, config_file, line_id);
		if (line_id != LINE_EMPTY)
			if (!(parsing_line(config, config_file->mapinfo[i], line_id)))
				exit(1);
		i++;
		if (present_info(config))
			break ;
	}
	validation_map(config, config_file, i);
	return (free_configfile(config_file), config);
}

// test
// t_config	*parser(int fd)
// {
// 	t_map		*config_file;
// 	t_config	*config;
// 	int			i;
// 	int			line_id;

// 	config_file = read_configfile(fd);
// 	if (!config_file)
// 		return (NULL);
// 	config = ft_calloc(sizeof(t_config), 1);
// 	if (!config)
// 		return (NULL);
// 	i = 0;
// 	while (i < config_file->height)
// 	{
// 		line_id = judge_line(config_file->mapinfo[i]);
// 		if (check_mapinfo_last(config,line_id))
// 			print_error("Enter only the necessary information and map information last.\n"),exit(1);
// 		if (line_id!=LINE_EMPTY)
// 			if (!(parsing_line(config,config_file->mapinfo[i],line_id)))
// 				exit(1);
// 		printf("\nconfin-check\n");
// 		printf("config,path-no = %s:apper %d\n",config->path_no.path,config->path_no.appear);
// 		printf("config,path-so = %s:apper %d\n",config->path_so.path,config->path_so.appear);
// 		printf("config,path-we = %s:apper %d\n",config->path_we.path,config->path_we.appear);
// 		printf("config,path-ea = %s:apper %d\n",config->path_ea.path,config->path_ea.appear);
// 		printf("config,floor : color[R] = %d color[G] = %d color[B] = %d : apper %d\n",config->floor.color[0],config->floor.color[1],config->floor.color[2],config->floor.appear);
// 		printf("config,ceil : color[R] = %d color[G] = %d color[B] = %d : apper %d\n",config->ceil.color[0],config->ceil.color[1],config->ceil.color[2],config->ceil.appear);
// 		i++;
// 		if (present_info(config))
// 			break ;
// 	}
// 	while (is_emptyline(config_file->mapinfo[i]))
// 		i++;
// 	config_file->map_h = i;
// 	validation_map(config, config_file, i);
// 	wp_free(&(config_file->mapinfo));
// 	free(config_file);
// 	printf("\ndirection is %c\n",config->p_direction);
// 	printf("start position[%d][%d] \n",config->y_position, config->x_position);
// 	return (config);
// }
