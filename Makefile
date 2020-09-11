# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/17 17:19:48 by kcedra            #+#    #+#              #
#    Updated: 2020/09/10 06:25:10 by kcedra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = cub3d

HEADER = cub3d.h

FLAGS = -Wall -Werror -Wextra

LIBFT_HEADER = libft/libft.h

LIBFT_MAKE = Makefile

LIBFT = libft.a

LIBFT_DIR = libft/

MLX_DIR = mlx/

MLX = libmlx.a

SOURCES = main.c parser.c parse_textures.c utils.c itoabase.c parse_colors.c \
errors_management.c draw_2d_map.c horizontal_raycaster.c vertical_raycaster.c put_image.c \
hooks_manage.c draw_texture.c

O_FILES = $(SOURCES:.c=.o)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(O_FILES)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)$(LIBFT) .
	make -C $(MLX_DIR)
	cp $(MLX_DIR)$(MLX) .
	$(CC) $(FLAGS) $(O_FILES) -L. -lft 	-L. -lmlx \
	-framework OpenGL -framework AppKit -o cub3d

clean:
	rm -f *.o
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f *.a
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean
	rm -f mlx/libmlx.a

re: fclean all
