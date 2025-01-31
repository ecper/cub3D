/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:03:45 by hauchida          #+#    #+#             */
/*   Updated: 2025/02/01 03:09:04 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_exit(t_config *config, t_map *config_file)
{
	all_free(config, config_file);
	exit(1);
}

int	open_cubfile(int argc, char *filename)
{
	int	len;
	int	fd;

	if (argc != 2)
		print_error("Error: please input one file that have a .cub extension");
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		print_error("Error:The file must have a .cub extension");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("Error:problem loading the file.");
	return (fd);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_config	*init_config;

	fd = open_cubfile(argc, argv[1]);
	*get_config() = parser(fd);
	init_t_data();
	return (0);
}
