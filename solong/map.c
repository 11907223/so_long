/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:30:34 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/05 15:19:14 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	save_map(char *file, t_map *map)
{
	int		fd;
	char	*line;
	char	*temp;
	int		i;
	int		linelen;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		linelen = ft_strlen(line);
		if (line[linelen - 1] == '\n')
			temp = ft_substr(line, 0, linelen - 1);
		map->array[i] = ft_strdup(temp);
		free(temp);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
}

static void	load_images(t_map *map, int img_width, int img_height)
{
	char	*main_char;
	char	*empty;
	char	*wall;
	char	*collectable;
	char	*exit;

	main_char = "textures/paris.xpm";
	empty = "textures/empty.xpm";
	wall = "textures/wall.xpm";
	collectable = "textures/louisbag.xpm";
	exit = "textures/exit.xpm";
	map->character = \
		mlx_xpm_file_to_image(map->mlx, main_char, &img_width, &img_height);
	map->empty = \
		mlx_xpm_file_to_image(map->mlx, empty, &img_width, &img_height);
	map->wall = \
		mlx_xpm_file_to_image(map->mlx, wall, &img_width, &img_height);
	map->collect = \
		mlx_xpm_file_to_image(map->mlx, collectable, &img_width, &img_height);
	map->exit = \
		mlx_xpm_file_to_image(map->mlx, exit, &img_width, &img_height);
	load_end(map, img_width, img_height);
}

static int	set_images(t_map *map)
{
	int	x;
	int	y;

	if (map->height < map->win_height)
		map->scale_y = (map->win_height - (map->height * TILE)) / 2;
	else
		map->scale_y = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			put_image(map, x, y);
			x++;
		}
		y++;
	}
	return (1);
}

static int	count_lines(char *file)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(file, O_RDONLY);
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

int	map_init(t_map *map, char *file)
{
	map->height = count_lines(file);
	map->array = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!map->array)
		return (-1);
	save_map(file, map);
	map->width = ft_strlen(map->array[0]);
	if (!valid_map(map))
		return (0);
	map->mlx = mlx_init();
	if (map->height * TILE > 400)
		map->win_height = map->height * TILE;
	else
		map->win_height = 400;
	map->win_width = map->width * TILE + 200;
	map->window = mlx_new_window(map->mlx, map->win_width, map->win_height, \
		"Paris Hilton <3");
	load_images(map, TILE, TILE);
	set_images(map);
	create_phone(map);
	return (1);
}
