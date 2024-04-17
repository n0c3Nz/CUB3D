# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 07:54:39 by smagniny          #+#    #+#              #
#    Updated: 2024/04/02 19:07:41 by guortun-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## COLORS ##
END = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
WHITE = \033[1;37m


#COMPILATION
NAME = Cub3D
CC = gcc -I./inc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
PATH_LIBFT = ./inc/Libft
PATH_GNL = ./inc/get_next_line

OS = $(shell uname)
#Linux o cualquier otro para incluir la mlx manualmente.

#Se necesitará cambiar los includes <mlx.h> por "mlx_linux/mlx.h" o "mlx_opengl/mlx.h"

#Hay distintos tipos de mlx, mlx_linux && mlx_opengl 
ifeq ($(OS),Linux)
    LFLAGS = -Linc/get_next_line -lget_next_line -Linc/Libft -lft -Linc/mlx_linux -lmlx -lm -lX11 -lXext 
#Darwin es para los PCs de 42 en donde uso la mlx que hay en el sistema. cambié los includes por <mlx.h>. 
else ifeq ($(OS),Darwin)
	LFLAGS = -L./inc/Libft -lft -L./inc/get_next_line -lget_next_line -Linc/mlx -lmlx -framework OpenGL -framework AppKit
#else ifeq ($(OS), Tupc)
#	LFLAGS = -Linc/get_next_line -lget_next_line -Linc/Libft -lft -Linc/mlx_opengl -lmlx -lm -framework OpenGL -framework AppKit
endif

OBJ_DIR = .obj
SRC_DIR = ./src

SRC = $(shell find $(SRC_DIR) -type f -name '*.c')

# SRC =  tests/01_untextured_raycast.c \
# 		./src/map_management/file_check.c \
# 		./src/map_management/file_check_2.c \
# 		./src/map_management/file_check_3.c \
# 		./src/map_management/map_check.c \
# 		./src/map_management/init_funcs.c \
		# ./src/graphic_funcs/mlx_process.c \
		# ./src/key_funcs/key_hook.c

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))


#REGLAS
all: $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@  $<

$(NAME): gnl libft $(OBJ)
	@echo "$(NAME): $(BLUE)Objects compiled succesdfully$(END)"
	@echo "$(NAME): $(BLUE)Linking...$(END)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
	@echo "$(NAME): $(BLUE)Cub3D created !$(END)"

#REMEMBER! MLX rule for compiling mlx on linux.

libft:
	@echo "$(NAME): $(BLUE)Generating Libft$(END)"
	@make -sC $(PATH_LIBFT)
	@echo "$(NAME): $(GREEN)Done!$(END)"

gnl:
	@echo "$(NAME): $(BLUE)Generating GNL$(END)"
	@make -sC $(PATH_GNL)
	@echo "$(NAME): $(GREEN)Done!$(END)"

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(BLUE)Deleting Libft$(END)"
	@make clean -sC $(PATH_LIBFT)
	@echo "$(NAME): $(BLUE)Deleting GNL$(END)"
	@make clean -sC $(PATH_GNL)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(PATH_LIBFT)
	@make fclean -C $(PATH_GNL)

re: fclean all

.PHONY: clean fclean all re libft gnl