/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 18:06:18 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/11 18:06:19 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 		move_forward(t_vars *vars)
{
	double x;
	double y;

	x = vars->player->x_pos;
	y = vars->player->y_pos;
	x += speed * cos(vars->player->pov);
	y += speed * sin(vars->player->pov);
	x = ceil(x) - x < x - floor(x) ? ceil(x) : floor(x);
	y = ceil(y) - y < y - floor(y) ? ceil(y) : floor(y);
	vars->player->x_pos = (int)x;
	vars->player->y_pos = (int)y;
	put_image(vars);
}

void 		move_backward(t_vars *vars)
{
	double x;
	double y;

	x = vars->player->x_pos;
	y = vars->player->y_pos;
	x += speed * cos(vars->player->pov + M_PI);
	y += speed * sin(vars->player->pov + M_PI);
	x = ceil(x) - x < x - floor(x) ? ceil(x) : floor(x);
	y = ceil(y) - y < y - floor(y) ? ceil(y) : floor(y);
	vars->player->x_pos = (int)x;
	vars->player->y_pos = (int)y;
	put_image(vars);
}

void 		move_left(t_vars *vars)
{
	double x;
	double y;
	double ray;

	x = vars->player->x_pos;
	y = vars->player->y_pos;
	ray = vars->player->pov - M_PI_2;
	x += speed * cos(ray);
	y += speed * sin(ray);
	x = ceil(x) - x < x - floor(x) ? ceil(x) : floor(x);
	y = ceil(y) - y < y - floor(y) ? ceil(y) : floor(y);
	vars->player->x_pos = (int)x;
	vars->player->y_pos = (int)y;
	put_image(vars);
}

void 		move_right(t_vars *vars)
{
	double x;
	double y;
	double ray;

	x = vars->player->x_pos;
	y = vars->player->y_pos;
	ray = vars->player->pov + M_PI_2;
	x += speed * cos(ray);
	y += speed * sin(ray);
	x = ceil(x) - x < x - floor(x) ? ceil(x) : floor(x);
	y = ceil(y) - y < y - floor(y) ? ceil(y) : floor(y);
	vars->player->x_pos = (int)x;
	vars->player->y_pos = (int)y;
	put_image(vars);
}

void 		rotate_left(t_vars *vars)
{
	vars->player->pov -= rotation_angle;
	put_image(vars);
}

void 		rotate_right(t_vars *vars)
{
	vars->player->pov += rotation_angle;
	put_image(vars);
}