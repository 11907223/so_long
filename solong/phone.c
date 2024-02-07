/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:54:12 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/05 13:16:27 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	init_steps(t_map *map, int size)
{
	int		i;
	char	*n;
	char	*temp;
	char	*path;

	i = 0;
	map->steps = (void **)ft_calloc(10, sizeof(void *));
	while (i < 10)
	{
		n = ft_itoa(i);
		temp = ft_strjoin("textures/", n);
		path = ft_strjoin(temp, ".xpm");
		map->steps[i] = mlx_xpm_file_to_image(map->mlx, path, &size, &size);
		free(n);
		free(temp);
		free(path);
		i++;
	}
	mlx_put_image_to_window(map->mlx, map->window, \
		map->steps[0], map->width * TILE + 30, 115);
	mlx_put_image_to_window(map->mlx, map->window, \
		map->steps[0], map->width * TILE + 75, 115);
	mlx_put_image_to_window(map->mlx, map->window, \
		map->steps[0], map->width * TILE + 120, 115);
}

void	print_steps(int step, t_map *map)
{
	char	*step_str;
	int		len;

	step_str = ft_itoa(step);
	len = ft_strlen(step_str);
	write(1, "your steps:", 12);
	write(1, &step_str[0], len);
	write(1, "\n", 1);
	if (step < 10)
		mlx_put_image_to_window(map->mlx, map->window, \
			map->steps[step], map->width * TILE + 120, 115);
	else if (step < 100)
	{
		mlx_put_image_to_window(map->mlx, map->window, \
			map->steps[step % 10], map->width * TILE + 120, 115);
		mlx_put_image_to_window(map->mlx, map->window, \
			map->steps[step / 10], map->width * TILE + 75, 115);
	}
	free(step_str);
}

void	create_phone(t_map *map)
{
	char	*phone;
	int		size;

	phone = "textures/phone.xpm";
	size = 400;
	map->phone = mlx_xpm_file_to_image(map->mlx, phone, &size, &size);
	mlx_put_image_to_window(map->mlx, map->window, \
		map->phone, map->width * TILE, 0);
	init_steps(map, TILE);
}
