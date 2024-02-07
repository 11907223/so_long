/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:41:31 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/05 15:49:17 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	get_positions(t_game *game, int x, int y)
{
	game->tot_collectibles = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.array[y][x] == 'C')
				game->tot_collectibles++;
			else if (game->map.array[y][x] == 'E')
			{
				game->exit.x = x;
				game->exit.y = y;
			}
			else if (game->map.array[y][x] == 'P')
			{
				game->player.x = x;
				game->player.y = y;
				game->oldplayer.x = x;
				game->oldplayer.y = y;
			}
			x++;
		}
		y++;
	}
	return (1);
}

static int	update_game(t_game *game)
{
	int	x;
	int	y;
	int	oldx;
	int	oldy;

	x = game->player.x * TILE;
	y = game->player.y * TILE;
	oldx = game->oldplayer.x * TILE;
	oldy = game->oldplayer.y * TILE;
	game->map.array[game->player.y][game->player.x] = 'P';
	game->map.array[game->oldplayer.y][game->oldplayer.x] = '0';
	mlx_put_image_to_window(game->map.mlx, game->map.window, \
		game->map.character, x, y + game->map.scale_y);
	mlx_put_image_to_window(game->map.mlx, game->map.window, \
		game->map.empty, oldx, oldy + game->map.scale_y);
	return (1);
}

static int	key_hook(int keycode, t_game *game)
{
	int	step;

	step = 0;
	game->oldplayer.x = game->player.x;
	game->oldplayer.y = game->player.y;
	if (keycode == 65362)
		step = make_move('y', -1, game);
	else if (keycode == 65363)
		step = make_move('x', 1, game);
	else if (keycode == 65364)
		step = make_move('y', 1, game);
	else if (keycode == 65361)
		step = make_move('x', -1, game);
	else if (keycode == 65307)
		clear_game(game);
	if (step == 1)
	{
		game->steps++;
		print_steps(game->steps, &game->map);
		update_game(game);
	}
	end_game(game, step);
	return (1);
}

int	game_init(t_game *game)
{
	char	**copy;

	game->bonus = create_enemies(game);
	if (game->bonus > 1)
		return (0);
	game->steps = 0;
	game->collected = 0;
	game->end = 0;
	game->round = 0;
	get_positions(game, 0, 0);
	copy = NULL;
	if (!check_path(game, copy, -1, -1))
		return (0);
	mlx_key_hook(game->map.window, key_hook, game);
	mlx_hook(game->map.window, \
		DestroyNotify, StructureNotifyMask, &clear_game, game);
	if (game->bonus)
		mlx_loop_hook(game->map.mlx, enemy_sprite, game);
	mlx_loop(game->map.mlx);
	return (1);
}
