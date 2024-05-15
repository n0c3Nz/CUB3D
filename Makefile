# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 07:54:39 by guortun-          #+#    #+#              #
#    Updated: 2024/05/15 10:44:31 by guortun-         ###   ########.fr        #
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
NAME = cub3D
CC = gcc -I./inc
CFLAGS = -Wall -Wextra -Werror #-g3  -fsanitize=address,leak 
PATH_LIBFT = ./inc/libft
PATH_GNL = ./inc/get_next_line
OS = $(shell uname)

ifeq ($(OS),Linux)
	PATH_MLX = ./inc/mlx_linux
    LFLAGS = -Linc/get_next_line -lget_next_line -Linc/libft -lft -Linc/mlx_linux -lmlx -lm -lX11 -lXext
else ifeq ($(OS),Darwin)
    PATH_MLX =./inc/mlx_opengl
    LFLAGS = -L./inc/Libft -lft -L./inc/get_next_line -lget_next_line -Linc/mlx_opengl -lmlx -framework OpenGL -framework AppKit
endif

GNL = $(PATH_GNL)/libget_next_line.a 
LIBFT = $(PATH_LIBFT)/libft.a
MLX = $(PATH_MLX)/libmlx.a

OBJ_DIR = .obj

SRC = ./src/graphic_funcs/ft_time.c \
		./src/graphic_funcs/render_floor_ceiling.c \
		./src/graphic_funcs/render_util.c \
		./src/graphic_funcs/render_walls.c \
		./src/graphic_funcs/mlx_process.c \
		./src/graphic_funcs/sprites.c \
		./src/init/init_cub.c \
		./src/init/init_graphics.c \
		./src/key_funcs/key_hook.c \
		./src/key_funcs/player_mouv.c \
		./src/map_management/file_check.c \
		./src/map_management/file_check_2.c \
		./src/map_management/file_check_3.c \
		./src/map_management/file_utils.c \
		./src/map_management/file_utils_2.c \
		./src/map_management/fill_map.c \
		./src/map_management/fill_map_utils.c \
		./src/map_management/freeee.c \
		./src/main.c \

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))


#REGLAS
all: $(NAME) 


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@  $<

$(NAME): $(OBJ) $(LIBFT) $(GNL) $(MLX)
	@echo "$(NAME): $(BLUE)Objects compiled succesdfully$(END)"
	@echo "$(NAME): $(BLUE)Linking...$(END)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
	@echo "$(NAME): $(BLUE)Cub3D created !$(END)"

$(MLX):
	@echo "$(NAME): $(BLUE)Generating MLX$(END)"
	@make -sC $(PATH_MLX)
	@echo "$(NAME): $(GREEN)Done!$(END)"

$(LIBFT):
	@echo "$(NAME): $(BLUE)Generating Libft$(END)"
	@make -sC $(PATH_LIBFT)
	@echo "$(NAME): $(GREEN)Done!$(END)"

$(GNL):
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
	@echo "$(NAME): $(BLUE)Deleting MLX$(END)"
	@make clean -sC $(PATH_MLX)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(PATH_LIBFT)
	@make fclean -C $(PATH_GNL)

re: fclean all

.PHONY: clean fclean all re libft gnl
