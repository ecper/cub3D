/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:22:56 by soaoki            #+#    #+#             */
/*   Updated: 2025/02/01 03:09:41 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	print_error(char *msg)
{
	const char	*red = "\033[31m";
	const char	*reset = "\033[0m";

	write(2, red, 5);
	ft_putendl_fd(msg, 1);
	write(2, reset, 4);
	exit(1);
}

void	wp_free(char ***str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		(*str)[i] = NULL;
		i++;
	}
	free(*str);
	*str = NULL;
}

void	free_configfile(t_map *config_file)
{
	if (!config_file)
		return ;
	if (config_file->mapinfo)
		wp_free(&(config_file->mapinfo));
	free(config_file);
}

void	free_config(t_config *config)
{
	if (config->path_ea.path)
		free(config->path_ea.path);
	if (config->path_no.path)
		free(config->path_no.path);
	if (config->path_we.path)
		free(config->path_we.path);
	if (config->path_so.path)
		free(config->path_so.path);
	if (config->map.mapinfo)
		wp_free(&(config->map.mapinfo));
	free(config);
}

void	all_free(t_config *config, t_map *config_file)
{
	free_configfile(config_file);
	free_config(config);
}
