/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:37:11 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/03 16:23:13 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_square(t_data *img, int *i, int *j, int color)//, int ***map)
{
	int width;
	int	height;
	
	height = *j + 64;
	//printf("==============================/nInside putsquare\n");
	while (*j < height)
	{
		// printf("Inside cycle of put\n");
		// printf("Value of i inside cycle = %d\n", *i);
		width = *i + 64;
		//printf("The value of j = %d\n", *j);
		while (*i < width)
		{
			//printf("Value of j inside cycle = %d\n", *j);
			//(*map)[*i][*j] = 1;
			my_mlx_pixel_put(img, *i, *j, color);
			*i = *i + 1;
		}
		//printf("Check for segfault\n");
		*i = width - 64;
		*j = *j + 1;
	}
}

void		draw_map(t_vars *vars, t_data *img, char **map)
{
	int		width;
	int		height;
	int		line;
	int		column;
	//int		**map_int;
	
	height = 0;
	line = 0;
	while (map[line] != NULL)
	{
		column = 0;
		width = 0;
		//printf("Value of i = %d\n", i);
		while (map[line][column] != '\0')
		{
			// printf("Map %d line - %s\n", line, map[line]);
			// printf("Inside cycle\n");
			// printf("Value of j = %d\n", j);
			if (map[line][column] == '1')
				put_square(img, &width, &height, 0x00FF0000);//, &map_int);
			if (map[line][column] == ' ')
				put_square(img, &width, &height, 0x00000000);//, &map_int);
			else if (map[line][column] == '0')
				put_square(img, &width, &height, 0x000000FF);//, &map_int);
			else if (map[line][column] == 'N')
				put_square(img, &width, &height, 0x0000FF00);//, &map_int);
			//printf("After predications\n");
			width += 64;
			height -= 64;
			column += 1;
		}
		line += 1;
		height += 64;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}