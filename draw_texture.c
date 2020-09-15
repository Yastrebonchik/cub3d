/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 20:17:30 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/15 23:36:56 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	draw_texture(t_vars *vars, int i, int *j, int height_of_wall)
{
	//int 	width;
	//int 	height;
	int 	cur_height;
	int 	coord;
	int 	color;
	double 	d_cur_height;

	if (vars->flag == 'W' || vars->flag == 'E')
		coord = (vars->map->coord_y % 64);
	else
		coord = vars->map->coord_x % 64;
	vars->map->coef = 64/(double)height_of_wall;
	d_cur_height = vars->map->coef * (double)(*j - ((vars->pars->res_y - height_of_wall) / 2));
	cur_height = floor(d_cur_height);
	//printf("%f\n", coef);
	//printf("I'm here\n");
	if (vars->flag == 'W')
		color = my_mlx_get_color(vars->west_texture, coord, cur_height);
	else if (vars->flag == 'S')
		color = my_mlx_get_color(vars->south_texture, coord, cur_height);
    else if (vars->flag == 'N')
		color = my_mlx_get_color(vars->north_texture, coord, cur_height);
	else
		color = my_mlx_get_color(vars->east_texture, coord, cur_height);
    //printf("And here\n");
	//while (*j < (vars->pars->res_y - height_of_wall) / 2 + height_of_wall)
	my_mlx_pixel_put(vars->data, i, (*j)++, color);
}