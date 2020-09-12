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

void	put_image(t_vars *vars)
{
	int		i;
	int		j;
	double 	current_ray;
	double 	distance;
	int		height_of_wall;
	//t_data	cur_image;
	//int		color;

	current_ray = vars->player->pov - M_PI / 6;
	if (current_ray <= 0)
		current_ray = 2 * M_PI + current_ray;
	i = 0;
	//cur_image.img = mlx_xpm_file_to_image(vars->mlx,
	//vars->pars->north_texture, &(cur_image.width), &(cur_image.height));
	//vars->cur_img = &cur_image;
	//if (cur_image.img == NULL)
	//{
	//	ft_putendl_fd("Error\nInvalid texture path file", 1);
	//	exit(1);
	//}
	while (i < vars->pars->res_x)
	{
		j = 0;
		if ((current_ray >= 3 * M_PI_2 - M_PI / 3 / vars->pars->res_x) && (current_ray <= 3 * M_PI_2 + M_PI / 3 / vars->pars->res_x))
			distance = horizontal_raycaster(vars->player->x_pos, vars->player->y_pos, 3 * M_PI_2, vars->map);//, line, column);
		else if ((current_ray >= M_PI - M_PI / 3 / vars->pars->res_x) && (current_ray <= M_PI + M_PI / 3 / vars->pars->res_x))
			distance = vertical_raycaster(vars->player->x_pos, vars->player->y_pos, M_PI, vars->map);//, line, column);
		else if ((current_ray >= M_PI_2 - M_PI / 3 / vars->pars->res_x) && (current_ray <= M_PI_2 + M_PI / 3 / vars->pars->res_x))
			distance = horizontal_raycaster(vars->player->x_pos, vars->player->y_pos, M_PI_2, vars->map);//, line, column);
		else if ((current_ray >= 2 * M_PI - M_PI / 3 / vars->pars->res_x) || (current_ray <= 0 + M_PI / 3 / vars->pars->res_x))
			distance = vertical_raycaster(vars->player->x_pos, vars->player->y_pos, 0, vars->map);//, line, column);
		else
			distance = min_of_2(vertical_raycaster(vars->player->x_pos, vars->player->y_pos, current_ray, vars->map),
			horizontal_raycaster(vars->player->x_pos, vars->player->y_pos, current_ray, vars->map));
		//printf("i = %d, distance = %f && current ray = %f\n", i, distance, current_ray);
		distance = distance * cos(-(M_PI / 6) + i * (M_PI / 3 / vars->pars->res_x));
		//printf("Distance = %f\n", distance);
		height_of_wall = scale / distance * (vars->pars->res_x / (2 * tan(M_PI / 6))) ;
		//color = atoi_color_base_16(pars.ceiling_color);
		//printf("Ceiling color = %s and it's int value is = %d\n", pars.ceiling_color, color);
		if (height_of_wall > vars->pars->res_y)
		{
			while (j < vars->pars->res_y)
				my_mlx_pixel_put(vars->data, i, j++, 0x00A52A2A);
		}
		else
		{
			while (j < (vars->pars->res_y - height_of_wall) / 2)
				my_mlx_pixel_put(vars->data, i, j++, 0x00ACAAA0);
			while (j < (vars->pars->res_y - height_of_wall) / 2 + height_of_wall)
				draw_texture(vars, i, &j, height_of_wall);
				//my_mlx_pixel_put(vars->data, i, j++, 0x00A52A2A);
			//color = atoi_color_base_16(pars.floor_color);
			//printf("Floor color = %s and it's int value is = %d\n", pars.floor_color, color);
			while (j < vars->pars->res_y)
				my_mlx_pixel_put(vars->data, i, j++, 0x000000FF);
		}
		i++;
		current_ray += M_PI / 3 / vars->pars->res_x;
		if (current_ray >= 2 * M_PI)
			current_ray = current_ray - 2 * M_PI;
		else if (current_ray <= 0)
			current_ray = 2 * M_PI + current_ray;
	}
	printf("POV = %f\n", vars->player->pov);
	printf("Players position x = %d\n", vars->player->x_pos);
	printf("Players position y = %d\n", vars->player->y_pos);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}
