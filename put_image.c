/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:54:31 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/07 21:00:47 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_image(t_data *img, double pov, t_pars pars, int line, int column, int x_pos, int y_pos, t_vars *vars)
{
	int		i;
	int		j;
	double 	current_ray;
	double 	distance;
	int		height_of_wall;
	//int		color;

	current_ray = pov - M_PI / 6;
	i = 0;
	printf("POV = %f\n", pov);
	while (i < pars.res_x)
	{
		j = 0;
		if ((current_ray >= 3 * M_PI_2 - M_PI / 3 / pars.res_x) && (current_ray <= 3 * M_PI_2 + M_PI / 3 / pars.res_x))
			distance = horizontal_raycaster(x_pos, y_pos, 3 * M_PI_2, pars.map, line, column);
		else if ((current_ray >= M_PI - M_PI / 3 / pars.res_x) && (current_ray <= M_PI + M_PI / 3 / pars.res_x))
			distance = vertical_raycaster(x_pos, y_pos, M_PI, pars.map, line, column);
		else if ((current_ray >= M_PI_2 - M_PI / 3 / pars.res_x) && (current_ray <= M_PI_2 + M_PI / 3 / pars.res_x))
			distance = horizontal_raycaster(x_pos, y_pos, M_PI_2, pars.map, line, column);
		else if ((current_ray >= 2 * M_PI - M_PI / 3 / pars.res_x) || (current_ray <= 0 + M_PI / 3 / pars.res_x))
			distance = vertical_raycaster(x_pos, y_pos, 0, pars.map, line, column);
		else
			distance = min_of_2(vertical_raycaster(x_pos, y_pos, current_ray, pars.map, line, column),
			horizontal_raycaster(x_pos, y_pos, current_ray, pars.map, line, column));
		//printf("i = %d, distance = %f && current ray = %f\n", i, distance, current_ray);
		height_of_wall = 64 * 1870.6 / distance;
		//color = atoi_color_base_16(pars.ceiling_color);
		//printf("Ceiling color = %s and it's int value is = %d\n", pars.ceiling_color, color);
		if (height_of_wall > pars.res_y)
		{
			while (j < pars.res_y)
			{
				my_mlx_pixel_put(img, i, j, 0x00FF0000);
				j++;
			}
		}
		else
		{
			while (j < (pars.res_y - height_of_wall) / 2)
				my_mlx_pixel_put(img, i, j++, 0x0000FF00);
			while (j < (pars.res_y - height_of_wall) / 2 + height_of_wall)
				my_mlx_pixel_put(img, i, j++, 0x00FF0000);
			//color = atoi_color_base_16(pars.floor_color);
			//printf("Floor color = %s and it's int value is = %d\n", pars.floor_color, color);
			while (j < pars.res_y)
				my_mlx_pixel_put(img, i, j++, 0x000000FF);
		}
		i++;
		current_ray += M_PI / 3 / pars.res_x;
		if (current_ray >= 2 * M_PI)
			current_ray = current_ray - 2 * M_PI;
		else if (current_ray <= 0)
			current_ray = 2 * M_PI + current_ray;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}