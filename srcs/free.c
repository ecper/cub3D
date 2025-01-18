/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:25:44 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/18 11:38:49 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_t_data(void)
{
	t_data *data;

	data = get_t_data();

	// if (data->win)
	// 	free(data->win);
	if (data->mlx)
		free(data->mlx);
}