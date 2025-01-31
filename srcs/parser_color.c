/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:21:00 by soaoki            #+#    #+#             */
/*   Updated: 2025/02/01 03:42:33 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_char(const char *str, char target)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == target)
			count++;
		str++;
	}
	return (count);
}

char	**check_numarray(char *line)
{
	char	**result;
	char	*trim_line;
	int		num_comma;

	line ++;
	trim_line = ft_trim_white(line);
	num_comma = count_char(trim_line, ',');
	result = ft_split(trim_line, ',');
	free(trim_line);
	if (!result)
		return (0);
	if (count_strarray(result) != 3 || num_comma != 2)
	{
		wp_free(&result);
		print_error("input only three colors R, G, B");
		return (NULL);
	}
	return (result);
}

int	set_color(t_config *config, char **color_array, int color_place)
{
	int	i;

	i = 0;
	while (i < MAX_COLOR)
	{
		if (color_place == FLOOR)
		{
			config->floor.color[i] = color_atoi(color_array[i]);
		}
		else if (color_place == CEIL)
		{
			config->ceil.color[i] = color_atoi(color_array[i]);
		}
		if (config->floor.color[i] == ATOI_ERROR
			|| config->ceil.color[i] == ATOI_ERROR)
		{	
			wp_free(&color_array);
			print_error("color range is from 0 to 255,only digit");
			return (0);
		}
		i ++;
	}
	return (1);
}

// example F 184,113,39
int	validation_color(t_config *config, char *line)
{
	int		color_place;
	char	**color_array;
	int		i;

	color_place = is_color(line);
	color_array = check_numarray(line);
	if (!color_array)
		return (0);
	i = 0;
	if (color_place == FLOOR && config->floor.appear == false)
	{
		if (!set_color(config, color_array, color_place))
			return (0);
		config->floor.appear = true;
	}
	else if (color_place == CEIL && config->ceil.appear == false)
	{
		if (!set_color(config, color_array, color_place))
			return (0);
		config->ceil.appear = true;
	}
	else
		return (wp_free(&color_array), ("Error : ID is one"), 0);
	wp_free(&color_array);
	return (1);
}

// int	validation_color(t_config *config, char *line)
// {
// 	int		color_place;
// 	char	**color_array;
// 	int		i;

// 	color_place = is_color(line);
// 	color_array = check_numarray(line);
// 	if (!color_array)
// 		return (0);
// 	i = 0;
// 	if (color_place == FLOOR && config->floor.appear == false)
// 	{
// 		while (i < MAX_COLOR)
// 		{
// 			config->floor.color[i] = color_atoi(color_array[i]);
// 			if (config->floor.color[i] == ATOI_ERROR)
// 			{	
// 				wp_free(&color_array);
// 				print_error("Error : color range is from 0 to 255,only digit");
// 				return (0);
// 			}
// 			i++;
// 		}
// 		config->floor.appear = true;
// 	}
// 	else if (color_place == CEIL && config->ceil.appear == false)
// 	{
// 		while (i < MAX_COLOR)
// 		{
// 			config->ceil.color[i] = color_atoi(color_array[i]);
// 			if (config->ceil.color[i] == ATOI_ERROR)
// 			{	
// 				wp_free(&color_array);
// 				print_error("Error : color range is from 0 to 255");
// 				return (0);
// 			}
// 			i++;
// 		}
// 		config->ceil.appear = true;
// 	}
// 	else
// 		return (wp_free(&color_array), ("Error : ID is one"), 0);
// 	wp_free(&color_array);
// 	return (1);
// }

// int	validation_color(t_config *config, char *line)
// {
// 	int		color_place;
// 	char	*trim_line;
// 	int		num_comma;
// 	char	**color_array;
// 	int		i;

// 	color_place = is_color(line);
// 	line ++;
// 	trim_line = ft_trim_white(line);
// 	num_comma = count_char(trim_line, ',');
// 	color_array = ft_split(trim_line, ',');
// 	free(trim_line);
// 	if (!color_array)
// 		return (0);
// 	if (count_strarray(color_array) != 3 || num_comma != 2)
// 	{
// 		wp_free(&color_array);
// 		print_error("Error : Enter only three colors R, G, B");
// 		return (0);
// 	}
// 	i = 0;
// 	if (color_place == FLOOR && config->floor.appear == false)
// 	{
// 		while (i < MAX_COLOR)
// 		{
// 			config->floor.color[i] = color_atoi(color_array[i]);
// 			if (config->floor.color[i] == ATOI_ERROR)
// 			{	
// 				wp_free(&color_array);
// 				print_error("Error : color range is from 0 to 255,only digit");
// 				return (0);
// 			}
// 			i++;
// 		}
// 		config->floor.appear = true;
// 	}
// 	else if (color_place == CEIL && config->ceil.appear == false)
// 	{
// 		while (i < MAX_COLOR)
// 		{
// 			config->ceil.color[i] = color_atoi(color_array[i]);
// 			if (config->ceil.color[i] == ATOI_ERROR)
// 			{	
// 				wp_free(&color_array);
// 				print_error("Error : color range is from 0 to 255");
// 				return (0);
// 			}
// 			i++;
// 		}
// 		config->ceil.appear = true;
// 	}
// 	else
// 	{
// 		print_error("Error : identifier is one");
// 		wp_free(&color_array);
// 		exit(1);
// 	}
// 	wp_free(&color_array);
// 	return (1);
// }