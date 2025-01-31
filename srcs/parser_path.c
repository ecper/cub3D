/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:18:14 by soaoki            #+#    #+#             */
/*   Updated: 2025/01/31 20:35:14 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_texture_path(t_config *config, char *path, int direction)
{
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
		return (0);
	return (1);
}

int	validation_path(t_config *config, char *line)
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
		return (print_error("Error:Only input tex path that have .xpm"), 0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("Error:Input correct tex path"), close(fd), 0);
	close(fd);
	if (!set_texture_path(config, path, direction))
	{
		if (path)
		{
			free(path);
			print_error("Error : identifier is one");
		}
		return (0);
	}
	return (1);
}

// int	validation_path(t_config *config, char *line)
// {
// 	char	*path;
// 	int		len;
// 	int		direction;
// 	int		fd;

// 	direction = is_texpath(line);
// 	line = line + 2;
// 	path = ft_trim_white(line);
// 	len = ft_strlen(path);
// 	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
// 		return (print_error("Error:Only input tex path that have .xpm"), 0);
// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 		return (print_error("Error:Input correct tex path"), close(fd), 0);
// 	close (fd);
// 	if (direction == NO && config->path_no.appear == false)
// 	{
// 		config->path_no.path = path;
// 		config->path_no.appear = true;
// 	}
// 	else if (direction == SO && config->path_so.appear == false)
// 	{
// 		config->path_so.path = path;
// 		config->path_so.appear = true;
// 	}
// 	else if (direction == WE && config->path_we.appear == false)
// 	{
// 		config->path_we.path = path;
// 		config->path_we.appear = true;
// 	}
// 	else if (direction == EA && config->path_ea.appear == false)
// 	{
// 		config->path_ea.path = path;
// 		config->path_ea.appear = true;
// 	}
// 	else
// 	{
// 		if (path)
// 		{	
// 			free(path);
// 			print_error("Error : identifier is one");
// 		}

// 	}
// 	return (1);
// }
