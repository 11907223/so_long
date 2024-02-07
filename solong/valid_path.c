/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:48:41 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/05 13:26:55 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	depth_first(t_game *game, char **map, int x, int y)
{
	if (y == game->player.y && x == game->player.x)
		return (1);
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (0);
	if (ft_strchr("1V", map[y][x]))
		return (0);
	if (game->start_tile == 'C' && map[y][x] == 'E')
		return (0);
	map[y][x] = 'V';
	if (depth_first(game, map, x - 1, y) || depth_first(game, map, x + 1, y) \
	|| (depth_first(game, map, x, y - 1) || depth_first(game, map, x, y + 1)))
		return (1);
	return (0);
}

static char	**copy_map(t_game *game)
{
	int		i;
	char	**new_map;

	i = 0;
	new_map = ft_calloc(game->map.height, sizeof(char *));
	while (i < game->map.height)
	{
		new_map[i] = ft_strdup(game->map.array[i]);
		i++;
	}
	return (new_map);
}

static void	free_map(char **map, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

static int	check_exit(t_game *game)
{
	char	**copy;

	copy = copy_map(game);
	game->start_tile = 'E';
	if (!depth_first(game, copy, game->exit.x, game->exit.y))
	{
		free_map(copy, game->map.height);
		return (0);
	}
	free_map(copy, game->map.height);
	return (1);
}

int	check_path(t_game *game, char **copy, int x, int y)
{
	if (!check_exit(game))
		return (0);
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			copy = copy_map(game);
			if (game->map.array[y][x] == 'C')
			{
				game->start_tile = 'C';
				if (!depth_first(game, copy, x, y))
				{
					free_map(copy, game->map.height);
					return (0);
				}
			}
			free_map(copy, game->map.height);
		}
	}
	game->start_tile = ' ';
	return (1);
}
