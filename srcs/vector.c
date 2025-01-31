/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:05:46 by hauchida          #+#    #+#             */
/*   Updated: 2025/02/01 03:07:26 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_vector	vector_sub(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

double	vector_mag(t_vector a)
{
	return ((a.x * a.x) + (a.y * a.y));
}
