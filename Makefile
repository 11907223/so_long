CC = cc
CFLAGS = -Wall -Werror -Wextra
XTRAFLAGS = -g -Ilibft
MLX_FLAGS = -Lmlx -L/usr/lib/X11 -lXext -lX11

NAME = so_long
LIBFT = libft/libft.a
MLX = minilibx/libmlx.a

SRC = solong/main.c solong/map.c solong/get_next_line.c solong/get_next_line_utils.c \
	solong/valid_map.c solong/game.c solong/moves.c solong/phone.c solong/enemies.c \
	solong/valid_path.c solong/move_enemy.c solong/gamemap_utils.c

OBJ = $(SRC:.c=.o)

all: libraries $(NAME)

$(NAME): $(OBJ) libraries
	$(CC) $(XTRAFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(XTRAFLAGS) -c $< -o $@

libraries:
	$(MAKE) -C minilibx
	$(MAKE) -C libft

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx clean

fclean: clean
	rm -f $(NAME) a.out *.gch so_long
	$(MAKE) -C libft fclean
	$(MAKE) -C minilibx fclean

re: fclean all

.PHONY: all clean fclean re
