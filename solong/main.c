/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:03:15 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/05 15:35:54 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	check_file(char *file_path)
{
	int		len;
	char	*type;

	if (!file_path || *file_path == '\0')
		return (0);
	len = ft_strlen(file_path);
	if (len < 4)
		return (0);
	type = ft_substr(file_path, len - 4, 4);
	if (!ft_strncmp(type, ".ber", 4))
	{
		free(type);
		return (1);
	}
	free(type);
	return (0);
}

static void	clear_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
		mlx_destroy_image(game->map.mlx, game->map.enemy[i++]);
	mlx_destroy_image(game->map.mlx, game->map.lost);
}

int	clear_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
		free(game->map.array[i++]);
	free(game->map.array);
	i = 0;
	while (i < 10)
		mlx_destroy_image(game->map.mlx, game->map.steps[i++]);
	free(game->map.steps);
	clear_enemies(game);
	mlx_clear_window(game->map.mlx, game->map.window);
	mlx_destroy_image(game->map.mlx, game->map.character);
	mlx_destroy_image(game->map.mlx, game->map.empty);
	mlx_destroy_image(game->map.mlx, game->map.wall);
	mlx_destroy_image(game->map.mlx, game->map.collect);
	mlx_destroy_image(game->map.mlx, game->map.exit);
	mlx_destroy_image(game->map.mlx, game->map.won);
	mlx_destroy_window(game->map.mlx, game->map.window);
	mlx_destroy_image(game->map.mlx, game->map.phone);
	mlx_destroy_display(game->map.mlx);
	free(game->map.mlx);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;

	if (argc != 2)
	{
		write(1, "Error\nGirlll provide a map! xoxo TTYN\n", 39);
		return (-1);
	}
	else if (!check_file(argv[1]) || !map_init(&game.map, argv[1]))
	{
		write(1, "Error\nGirlll provide a valid map! xoxo TTYN\n", 45);
		i = 0;
		while (i < game.map.height)
			free(game.map.array[i++]);
		free(game.map.array);
		return (-1);
	}
	else if (!game_init(&game))
	{
		write(1, "Error\nGirlll provide a valid map! xoxo TTYN\n", 45);
		clear_game(&game);
		return (-1);
	}
	return (1);
}
