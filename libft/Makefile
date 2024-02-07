NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_memset.c ft_memcpy.c ft_bzero.c\
	ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
	ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
	ft_strnstr.c ft_atoi.c count_digits.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putnbr_base_fd.c \

BSRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

TESTSRC = main.c

OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)
TESTOBJ = $(TESTSRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BOBJ) $(NAME)
	ar rc $(NAME) $(BOBJ)

test: $(TESTOBJ) $(NAME)
	$(CC) $(CFLAGS) main.c $(NAME) && ./a.out

clean:
	rm -f $(OBJ) $(BOBJ) $(TESTOBJ)

fclean: clean
	rm -f $(NAME) *.gch libft.a

re: fclean all

.PHONY: all clean fclean re
