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
	//int		fd;
	double 	current_ray;
	double 	distance;
	int		height_of_wall;
	//int		color;

	current_ray = pov - M_PI / 6;
	i = 0;
	//fd = open("Distances", O_WRONLY);
	while (i < 1920)
	{
		j = 0;
		if ((current_ray >= 3 * M_PI_2 - M_PI / 3 / 1980) && (current_ray <= 3 * M_PI_2 + M_PI / 3 / 1980))
			distance = horizontal_raycaster(x_pos, y_pos, 3 * M_PI_2, pars.map, line, column);
		else
			distance = min_of_2(vertical_raycaster(x_pos, y_pos, current_ray, pars.map, line, column),
			horizontal_raycaster(x_pos, y_pos, current_ray, pars.map, line, column));
		printf("i = %d, distance = %f && current ray = %f\n", i, distance, current_ray);
		//i++;
		//current_ray += M_PI / 3 / 1980;
		//distance = distance * cos(current_ray);
		height_of_wall = 64 * 1870.6 / distance;
		//printf("Inside drawer\n");
		//color = atoi_color_base_16(pars.ceiling_color);
		while (j < (1080 - height_of_wall) / 2)
		{
			my_mlx_pixel_put(img, i, j, 0x0000FF00);
			j++;
		}
		while (j < (1080 - height_of_wall) / 2 + height_of_wall)
		{
			my_mlx_pixel_put(img, i, j, 0x00FF0000);
			j++;
		}
		//color = atoi_color_base_16(pars.floor_color);
		while (j < 1080)
		{
			my_mlx_pixel_put(img, i, j, 0x000000FF);
			j++;
		}
		i++;
		current_ray += M_PI / 3 / 1980;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}