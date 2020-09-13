/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 20:17:30 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/11 20:17:35 by kcedra           ###   ########.fr       */
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
	double 	coef;
	double 	d_cur_height;

	coord = (vars->map->coord % 64);
	vars->map->coef = 64/(double)height_of_wall;
	d_cur_height = vars->map->coef * (double)(*j - ((vars->pars->res_y - height_of_wall) / 2));
	cur_height = floor(d_cur_height);
	//printf("%f\n", coef);
	color = my_mlx_get_color(vars->cur_img, coord, cur_height);
	//while (*j < (vars->pars->res_y - height_of_wall) / 2 + height_of_wall)
	my_mlx_pixel_put(vars->data, i, (*j)++, color);
}