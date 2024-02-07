/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamemap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:59:56 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/05 13:16:27 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	load_end(t_map *map, int img_width, int img_height)
{
	char	*won;

	won = "textures/won.xpm";
	map->won = \
		mlx_xpm_file_to_image(map->mlx, won, &img_width, &img_height);
}

void	put_image(t_map *map, int x, int y)
{
	if (map->array[y][x] == '0')
		mlx_put_image_to_window(map->mlx, map->window, \
			map->empty, x * TILE, y * TILE + map->scale_y);
	else if (map->array[y][x] == '1')
		mlx_put_image_to_window(map->mlx, map->window, \
			map->wall, x * TILE, y * TILE + map->scale_y);
	else if (map->array[y][x] == 'C')
		mlx_put_image_to_window(map->mlx, map->window, \
			map->collect, x * TILE, y * TILE + map->scale_y);
	else if (map->array[y][x] == 'E')
		mlx_put_image_to_window(map->mlx, map->window, \
			map->exit, x * TILE, y * TILE + map->scale_y);
	else if (map->array[y][x] == 'P')
		mlx_put_image_to_window(map->mlx, map->window, \
			map->character, x * TILE, y * TILE + map->scale_y);
}

void	end_game(t_game *game, int end)
{
	if (end == -1)
	{
		game->end = 1;
		mlx_put_image_to_window(game->map.mlx, game->map.window, \
			game->map.won, game->map.width * TILE / 2 - 200, 0);
	}
	else if (end == -2)
	{
		game->end = 1;
		mlx_put_image_to_window(game->map.mlx, game->map.window, \
			game->map.lost, game->map.width * TILE / 2 - 200, 0);
	}
}
