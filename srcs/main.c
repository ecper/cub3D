/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:03:45 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/24 18:20:32 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
int	main(int argc,char **argv)
{
	int fd;
	t_config *config;
	
	fd = open_cubfile(argc, argv[1]); // openのエラーとエクステンションの確認
	config =parser(fd);
	//init_t_dataにconfigを渡して初期化する。
	init_t_data();

	// mlx_mouse_hook(data.win, mouse_hook, &data);
	// mlx_key_hook(data.win, key_hook, &data);
	// mlx_hook(data.win, CROSS_BUTTON, 0, close_window, &data);
	// mlx_expose_hook(data.win, key_hook, &data);
	// mlx_loop_hook(data.mlx, render, &data);
	// mlx_loop(data.mlx);
	
	return (0);
}