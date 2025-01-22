/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:24 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/23 00:01:03 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	with2p(t_vector begin, t_vector end)
{
	t_ray	result;

	result.pos.x = begin.x;
	result.pos.y = begin.y;
	result.way = vector_sub(end, begin);
	return (result);
}

t_vector	ray_begin(t_ray ray)
{
	return (ray.pos);
}

t_vector	ray_end(t_ray ray)
{
	t_vector result;

	result = vector_add(ray.pos, ray.way);
	return (result);
}