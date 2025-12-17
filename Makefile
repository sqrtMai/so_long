NAME = so_long
CC = cc -Wall -Wextra -Werror
CFLAGS = -I./libft -I./ -Imlx_linux
AR = ar rcs
RM = rm -f

SRC = so_long.c hook.c so_long_utils.c so_long_utils2.c initialize.c check_map.c error_handling.c update_player_pos.c draw_textures.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJ) -L./libft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ./libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
