/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:46:15 by hauchida          #+#    #+#             */
/*   Updated: 2025/01/27 21:40:32 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_square	*create_square(int x, int y)
{
	t_square	*new;

	new = (t_square *)malloc(sizeof(t_square));
	if (!new)
		return (NULL);
	new->top = with2p((t_vector){x, y}, (t_vector){x + SQUARE_SIZE, y});
	new->down = with2p((t_vector){x, y + SQUARE_SIZE}, (t_vector){x
			+ SQUARE_SIZE, y + SQUARE_SIZE});
	new->left = with2p((t_vector){x, y}, (t_vector){x, y + SQUARE_SIZE});
	new->right = with2p((t_vector){x + SQUARE_SIZE, y}, (t_vector){x
			+ SQUARE_SIZE, y + SQUARE_SIZE});
	new->next = NULL;
	return (new);
}

void	add_square(t_square *new)
{
	t_square	**top_square;

	if (!new)
		return ;
	top_square = get_square();
	if (*top_square == NULL)
		*top_square = new;
	else
	{
		new->next = *top_square;
		*top_square = new;
	}
}
