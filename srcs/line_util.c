/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:15:57 by soaoki            #+#    #+#             */
/*   Updated: 2025/02/01 00:52:32 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	check_mapinfo_last(t_config *config, t_map *config_file, int line_id)
{
	if (line_id == LINE_MAP)
	{
		if (config->ceil.appear && config->floor.appear
			&& config->path_ea.appear && config->path_no.appear
			&& config->path_so.appear && config->path_we.appear)
			return (0);
		else
		{
			print_error("Enter only config info and map info last.\n");
			free_exit(config, config_file);
		}
	}
	else
		return (0);
}
