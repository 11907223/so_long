/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:51 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/05 15:23:08 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <unistd.h>
# include "../minilibx/mlx_int.h"
# include "../minilibx/mlx.h"
# include "getnextline.h"
# include "../libft/libft.h"

# define TILE 50
# define LEVEL 1
# define FRAMES 5

typedef struct s_coordinates {
	int	x;
	int	y;
}	t_coordinates;

typedef struct s_map {
	void	*mlx;
	void	*window;
	int		width;
	int		height;
	int		win_width;
	int		win_height;
	int		scale_y;
	char	**array;
	char	*character;
	char	*empty;
	char	*wall;
	char	*collect;
	char	*exit;
	char	*won;
	char	*lost;
	char	*phone;
	void	**enemy[5];
	void	**steps;
}	t_map;

typedef struct s_game {
	t_map			map;
	int				tot_collectibles;
	t_coordinates	exit;
	t_coordinates	player;
	t_coordinates	oldplayer;
	t_coordinates	enemy;
	int				collected;
	int				steps;
	int				end;
	char			start_tile;
	int				round;
	int				bonus;
}	t_game;

// Functions to initialize and validate map
int		valid_map(t_map *map);
int		map_init(t_map *map, char *file);
void	load_end(t_map *map, int img_width, int img_height);
void	put_image(t_map *map, int x, int y);
void	create_phone(t_map *map);
int		check_path(t_game *game, char **copy, int x, int y);

// Create and play with enemies
int		create_enemies(t_game *game);
int		move_enemy(t_game *game);
int		enemy_sprite(t_game *game);
void	delay(unsigned int milliseconds);

// Functions to initialize and play game
int		game_init(t_game *game);
int		make_move(char axis, int direction, t_game *game);
int		clear_game(t_game *game);
void	print_steps(int steps, t_map *map);
void	end_game(t_game *game, int end);

#endif
