/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:03:45 by hauchida          #+#    #+#             */
/*   Updated: 2025/02/01 06:19:48 by hauchida         ###   ########.fr       */
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
	{
		print_error("please input one file that have a .cub extension");
		exit(1);
	}
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		print_error("The file must have a .cub extension");
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("problem loading the file.");
		exit(1);
	}
	return (fd);
}

int	main(int argc, char **argv)
{
	int	fd;

	fd = open_cubfile(argc, argv[1]);
	*get_config() = parser(fd);
	init_t_data();
	return (0);
}
