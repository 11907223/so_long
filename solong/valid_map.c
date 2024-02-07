/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:23:10 by evan-ite          #+#    #+#             */
/*   Updated: 2024/01/31 15:22:34 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	check_shapenchars(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		if (ft_strlen(map->array[y]) != (size_t)map->width)
			return (0);
		x = 0;
		while (x < map->width)
		{
			if (!ft_strchr("01CEPX", map->array[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	check_walls(t_map *map)
{
	int		y;
	char	*top;
	char	*bottom;

	top = map->array[0];
	bottom = map->array[map->height - 1];
	if (ft_strchr(top, '0') || ft_strchr(bottom, '0'))
		return (0);
	else if (ft_strchr(top, 'E') || ft_strchr(bottom, 'E'))
		return (0);
	else if (ft_strchr(top, 'C') || ft_strchr(bottom, 'C'))
		return (0);
	else if (ft_strchr(top, 'P') || ft_strchr(bottom, 'P'))
		return (0);
	y = 0;
	while (y < map->height)
	{
		if (map->array[y][0] != '1' || map->array[y][map->width - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

static int	check_elements(t_map *map, int x, int y)
{
	int	exit_count;
	int	player_count;
	int	collect_count;

	exit_count = 0;
	player_count = 0;
	collect_count = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->array[y][x] == 'C')
				collect_count++;
			else if (map->array[y][x] == 'E')
				exit_count++;
			else if (map->array[y][x] == 'P')
				player_count++;
			x++;
		}
		y++;
	}
	if (collect_count < 1 || exit_count > 1 || player_count > 1)
		return (0);
	return (1);
}

int	valid_map(t_map *map)
{
	if (!check_shapenchars(map) || !check_elements(map, 0, 0))
		return (0);
	else if (!check_walls(map))
		return (0);
	else
		return (1);
}
