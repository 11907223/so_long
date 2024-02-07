/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:36:12 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/05 13:57:47 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <time.h>

static int	update_position(t_game *game, char xy, int direction)
{
	if (xy == 'x')
	{
		if (game->map.array[game->enemy.y][game->enemy.x + direction] == '0')
		{
			game->enemy.x += direction;
			game->map.array[game->enemy.y][game->enemy.x] = 'X';
			return (1);
		}
		if (game->map.array[game->enemy.y][game->enemy.x + direction] == 'P')
			game->end = 1;
	}
	else if (xy == 'y')
	{
		if (game->map.array[game->enemy.y + direction][game->enemy.x] == '0')
		{
			game->enemy.y += direction;
			game->map.array[game->enemy.y][game->enemy.x] = 'X';
			return (1);
		}
		if (game->map.array[game->enemy.y + direction][game->enemy.x] == 'P')
			game->end = 1;
	}
	return (0);
}

int	move_enemy(t_game *game)
{
	int	directions[2];
	int	xy[2];
	int	randomdir;
	int	randomxy;

	srand(time(NULL));
	directions[0] = -1;
	directions[1] = 1;
	xy[0] = 0;
	xy[1] = 1;
	game->map.array[game->enemy.y][game->enemy.x] = '0';
	while (1)
	{
		if (game->end)
			return (-1);
		randomdir = directions[rand() % 2];
		randomxy = xy[rand() % 2];
		if (!randomxy)
		{
			if (update_position(game, 'x', randomdir))
				return (1);
		}
		if (update_position(game, 'y', randomdir))
			return (1);
	}
}
