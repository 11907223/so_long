/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:48:44 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/05 15:48:46 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <stdio.h>
#include <time.h>

static int	find_enemies(t_game *game, t_map *map)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->array[y][x] == 'X')
			{
				game->enemy.x = x;
				game->enemy.y = y;
				count++;
			}
			x++;
		}
		y++;
	}
	return(count);
}

static int	init_enemy(t_game *game, int size)
{
	int		i;
	char	*n;
	char	*temp;
	char	*path;

	i = 1;
	while (i < FRAMES + 1)
	{
		n = ft_itoa(i);
		temp = ft_strjoin("textures/enemy", n);
		path = ft_strjoin(temp, ".xpm");
		game->map.enemy[i - 1] = \
		mlx_xpm_file_to_image(game->map.mlx, path, &size, &size);
		free(n);
		free(temp);
		free(path);
		i++;
	}
	return (find_enemies(game, &game->map));
}

int	enemy_sprite(t_game *game)
{
	static int	frame = 0;

	game->round++;
	if (game->end != 0)
		return (1);
	if (game->round % (55000 / LEVEL) == 0)
	{
		mlx_put_image_to_window(game->map.mlx, game->map.window, \
			game->map.empty, game->enemy.x * TILE, \
			game->enemy.y * TILE + game->map.scale_y);
		if (move_enemy(game) == -1)
		{
			mlx_put_image_to_window(game->map.mlx, game->map.window, \
				game->map.lost, game->map.width * TILE / 2 - 200, 0);
			game->end = -2;
			return (1);
		}
		frame = (frame + 1) % FRAMES;
		mlx_put_image_to_window(game->map.mlx, game->map.window, \
			game->map.enemy[frame], game->enemy.x * TILE, \
			game->enemy.y * TILE + game->map.scale_y);
	}
	return (0);
}

int	create_enemies(t_game *game)
{
	char	*lost;
	int		size;
	int		enemy_count;

	lost = "textures/lost.xpm";
	size = TILE;
	game->map.lost = mlx_xpm_file_to_image(game->map.mlx, lost, &size, &size);
	enemy_count = init_enemy(game, TILE);
	mlx_put_image_to_window(game->map.mlx, game->map.window, \
		game->map.enemy[0], game->enemy.x * TILE, \
		game->enemy.y * TILE + game->map.scale_y);
	return (enemy_count);
}
