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

	//printf("North texture is - %s\n", vars->pars->north_texture);
	height_of_wall = 3;
	my_mlx_pixel_put(vars->data, i, (*j)++, 0x00A52A2A);
}