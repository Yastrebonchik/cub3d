/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:54:31 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/23 15:55:58 by alexander        ###   ########.fr       */
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
	int		color;

	current_ray = vars->player->pov - M_PI / 6;
	if (current_ray <= 0)
		current_ray = 2 * M_PI + current_ray;
	i = 0;
	//printf("Players position x = %d\n", vars->player->x_pos);
	//printf("Players position y = %d\n", vars->player->y_pos);
	//printf("POV = %f\n", vars->player->pov);
	while (i < vars->pars->res_x)
	{
		if ((current_ray >= 3 * M_PI_2 - M_PI / 3 / vars->pars->res_x) && (current_ray <= 3 * M_PI_2 + M_PI / 3 / vars->pars->res_x))
			distance = horizontal_raycaster(vars->player->x_pos, vars->player->y_pos, 3 * M_PI_2, vars->map);
		else if ((current_ray >= M_PI - M_PI / 3 / vars->pars->res_x) && (current_ray <= M_PI + M_PI / 3 / vars->pars->res_x))
        {
			distance = vertical_raycaster(vars->player->x_pos, vars->player->y_pos, M_PI, vars->map);
            vars->flag = 'E';
        }
        else if ((current_ray >= M_PI_2 - M_PI / 3 / vars->pars->res_x) && (current_ray <= M_PI_2 + M_PI / 3 / vars->pars->res_x))
			distance = horizontal_raycaster(vars->player->x_pos, vars->player->y_pos, M_PI_2, vars->map);
		else if ((current_ray >= 2 * M_PI - M_PI / 3 / vars->pars->res_x) || (current_ray <= 0 + M_PI / 3 / vars->pars->res_x))
			distance = vertical_raycaster(vars->player->x_pos, vars->player->y_pos, 0, vars->map);
		else
			distance = min_of_2_cub(vertical_raycaster(vars->player->x_pos, vars->player->y_pos, current_ray, vars->map),
			horizontal_raycaster(vars->player->x_pos, vars->player->y_pos, current_ray, vars->map), vars);
		//printf("i = %04d, distance = %f && current ray = %f and coord for textures = %4d\n", i, distance, current_ray, vars->map->coord);
		if (distance == 0)
			break;
		distance = distance * cos(-(M_PI / 6) + i * (M_PI / 3 / vars->pars->res_x));
		vars->dst[i] = distance;
		height_of_wall = scale / distance * (vars->pars->res_x / (2 * tan(M_PI / 6)));
        check_side_of_world(vars, current_ray);
		color = atoi_color_base_16(vars->pars->ceiling_color);
		//printf("Ceiling color = %s and it's int value is = %d\n", vars->pars->floor_color, color);
		vars->map->texture_scale = 64/(double)height_of_wall;
		j = 0;
		if (height_of_wall > vars->pars->res_y)
		{
			while (j < vars->pars->res_y)
				draw_texture(vars, i, &j, height_of_wall);
		}
		else
		{
			while (j < (vars->pars->res_y - height_of_wall) / 2)
				my_mlx_pixel_put(vars->data, i, j++, color);
			while (j < (vars->pars->res_y - height_of_wall) / 2 + height_of_wall)
				draw_texture(vars, i, &j, height_of_wall);
			color = atoi_color_base_16(vars->pars->floor_color);
			//printf("Floor color = %s and it's int value is = %d\n", vars->pars->floor_color, color);
			while (j < vars->pars->res_y)
				my_mlx_pixel_put(vars->data, i, j++, color);
		}
		i++;
		current_ray += M_PI / 3 / vars->pars->res_x;
		if (current_ray >= 2 * M_PI)
			current_ray = current_ray - 2 * M_PI;
		else if (current_ray <= 0)
			current_ray = 2 * M_PI + current_ray;
        //printf("%c\n", vars->flag);
	}
	check_sprites(vars);
	//if (i == vars->pars->res_x)
	//printf("Kekos\n");
	//print_textures(vars->map);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}