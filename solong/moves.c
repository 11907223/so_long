/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:39:44 by evan-ite          #+#    #+#             */
/*   Updated: 2024/01/31 15:25:40 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	check_move(t_game *game, char new_tile)
{
	if (new_tile != '1')
	{
		if (new_tile == 'X')
			return (-2);
		if (new_tile == 'C')
			game->collected++;
		if (new_tile == 'E')
		{
			if (game->collected >= game->tot_collectibles)
			{
				game->end = 1;
				return (-1);
			}
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

int	make_move(char axis, int direction, t_game *game)
{
	char	new_tile;
	int		result;
	int		y;
	int		x;

	result = 0;
	if (axis == 'y' && !game->end)
	{
		y = game->player.y + (direction * 1);
		new_tile = game->map.array[y][game->player.x];
		result = check_move(game, new_tile);
		if (result == 1)
			game->player.y = game->player.y + (direction * 1);
	}
	else if (axis == 'x' && !game->end)
	{
		x = game->player.x + (direction * 1);
		new_tile = game->map.array[game->player.y][x];
		result = check_move(game, new_tile);
		if (result == 1)
			game->player.x = game->player.x + (direction * 1);
	}
	return (result);
}
