/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:01:30 by soaoki            #+#    #+#             */
/*   Updated: 2025/02/01 06:28:57 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

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
				free_exit(config, config_file);
		i++;
		if (present_info(config))
			break ;
	}
	validation_map(config, config_file, i);
	return (free_configfile(config_file), config);
}
