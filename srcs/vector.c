/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:05:46 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/22 19:09:50 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vector_plus(t_vector *result, t_vector a, t_vector b)
{
	result->x = a.x + b.x;
	result->y = a.y + b.y;
}

void	vector_minus(t_vector *result, t_vector a, t_vector b)
{
	result->x = a.x - b.x;
	result->y = a.y - b.y;
}