/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:24 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/24 00:50:18 by hauchida         ###   ########.fr       */
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
	t_vector	result;

	result = vector_add(ray.pos, ray.way);
	return (result);
}

t_vector	*calc_intersection(t_ray ray1, t_ray ray2)
{
	double t1 = ray1.way.x / ray1.way.y;
	double t2 = ray2.way.x / ray2.way.y;

	double sx = t1 * ray1.pos.x - t2 * ray2.pos.x - ray1.pos.y + ray2.pos.y
		/ (t1 - t2);

	double sy = t1 * (sx - ray1.pos.x) + ray1.pos.y;

	if (sx > min(ray_begin(ray1).x, ray_end(ray1).x)
		&& sx < max(ray_begin(ray1).x, ray_end(ray1).x)
		&& sx > min(ray_begin(ray2).x, ray_end(ray2).x)
		&& sx < max(ray_begin(ray2).x, ray_end(ray2).x))
	{
		return (&(t_vector){sx, sy});
	}
	else
	{
		return (NULL);
	}
}
