/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:54:31 by kcedra            #+#    #+#             */
/*   Updated: 2020/10/03 21:53:52 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_distance(t_vars *vars, double current_ray)
{
	if ((current_ray >= 3 * M_PI_2 - M_PI / 3 / vars->pars->res_x) &&
	(current_ray <= 3 * M_PI_2 + M_PI / 3 / vars->pars->res_x))
		return (horizontal_raycaster(vars->player->x_pos, vars->
		player->y_pos, 3 * M_PI_2, vars->map));
	else if ((current_ray >= M_PI - M_PI / 3 / vars->pars->res_x) && 
	current_ray <= M_PI + M_PI / 3 / vars->pars->res_x)
    {
		vars->flag = 'E';
		return (vertical_raycaster(vars->player->x_pos, vars->player->y_pos,
		M_PI, vars->map));
	}
	else if ((current_ray >= M_PI_2 - M_PI / 3 / vars->pars->res_x) &&
	(current_ray <= M_PI_2 + M_PI / 3 / vars->pars->res_x))
		return (horizontal_raycaster(vars->player->x_pos,
		vars->player->y_pos, M_PI_2, vars->map));
	else if ((current_ray >= 2 * M_PI - M_PI / 3 / vars->pars->res_x) ||
	(current_ray <= 0 + M_PI / 3 / vars->pars->res_x))
		return (vertical_raycaster(vars->player->x_pos,
		vars->player->y_pos, 0, vars->map));
	else
		return (min_of_2_cub(vertical_raycaster(vars->player->x_pos,
		vars->player->y_pos, current_ray, vars->map),
		horizontal_raycaster(vars->player->x_pos, vars->player->y_pos,
		current_ray, vars->map), vars));
}

static void		paint_column(t_vars *vars, int i, int height_of_wall)
{
	int		j;
	int		color;
	
	j = 0;
	color = atoi_color_base_16(vars->pars->ceiling_color);
	if (height_of_wall > vars->pars->res_y)
	{
		while (j < vars->pars->res_y)
			draw_texture(vars, i, &j, height_of_wall);
	}
	else
	{
		while (j < (vars->pars->res_y - height_of_wall) / 2)
			my_mlx_pixel_put(vars->data, i, j++, color);
		while (j < (vars->pars->res_y - height_of_wall) / 2
		+ height_of_wall)
			draw_texture(vars, i, &j, height_of_wall);
		color = atoi_color_base_16(vars->pars->floor_color);
		while (j < vars->pars->res_y)
			my_mlx_pixel_put(vars->data, i, j++, color);
	}
}

static void		paint_image(t_vars *vars, double current_ray)
{
	int		i;
	int		height_of_wall;
	double	distance;

	i = 0;
	while (i < vars->pars->res_x)
	{
		distance = get_distance(vars, current_ray);
		if (distance == 0)
			break;
		vars->dst[i] = distance;
		distance = distance * cos(-(M_PI / 6) + i * (M_PI / 3 /
		vars->pars->res_x));
		height_of_wall = scale / distance * (vars->pars->res_x /
		(2 * tan(M_PI / 6)));
        check_side_of_world(vars, current_ray);
		vars->map->texture_scale = 64/(double)height_of_wall;
		paint_column(vars, i, height_of_wall);
		i++;
		current_ray += M_PI / 3 / vars->pars->res_x;
		if (current_ray >= 2 * M_PI)
			current_ray = current_ray - 2 * M_PI;
		else if (current_ray <= 0)
			current_ray = 2 * M_PI + current_ray;
	}
}

void			put_image(t_vars *vars)
{
	double 	current_ray;

	current_ray = vars->player->pov - M_PI / 6;
	if (current_ray <= 0)
		current_ray = 2 * M_PI + current_ray;
	paint_image(vars, current_ray);
	check_sprites(vars);
	mlx_do_sync(vars->mlx);
	if (vars->screenshot_flag != 1)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}