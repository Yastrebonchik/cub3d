# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexander <alexander@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/17 17:19:48 by kcedra            #+#    #+#              #
#    Updated: 2020/09/28 23:41:42 by alexander        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = cub3d

HEADER = cub3d.h

FLAGS = -Wall -Werror -Wextra

LIBFT_HEADER = libft/libft.h

LIBFT_MAKE = Makefile

LIBFT = libft.a

LIBFT_DIR = libft/

MLX_DIR = mlx/

MLX = libmlx.dylib

SOURCES = main.c parser.c parse_textures.c utils.c itoabase.c parse_colors.c \
errors_management.c horizontal_raycaster.c vertical_raycaster.c put_image.c \
hooks_manage.c draw_texture.c color_funcs.c map_utils.c sprite_list_init.c draw_sprites.c \
map_validity_check.c map_walls_surrounding.c errors_management_utils.c make_screenshot.c \
textures_init.c vertical_raycaster_utils.c horizontal_raycaster_utils.c

O_FILES = $(SOURCES:.c=.o)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(O_FILES)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)$(LIBFT) .
	make -C $(MLX_DIR)
	cp $(MLX_DIR)$(MLX) .
	$(CC) $(FLAGS) $(O_FILES) -L. -lft 	-L. -lmlx -framework OpenGL -framework AppKit -o cub3d

clean:
	rm -f *.o
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f *.a
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean
	rm -f $(MLX_DIR)$(MLX)

re: fclean all
