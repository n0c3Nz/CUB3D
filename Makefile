NAME = Cub3D

CC = gcc -I./inc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
LFLAGS = -L./inc/Libft -lft -L./inc/mlx -L./inc/get_next_line -lget_next_line -lmlx -framework OpenGL -framework AppKit

SRC = main.c \
		./src/map_management/map_check.c \
		./src/map_management/map_check_2.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re