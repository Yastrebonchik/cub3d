/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 18:06:18 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/15 23:36:38 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Коллизия работает не идеально, при попадании на граничное значение,
на 64 например, происходит вылет из-за леления на бесконечность 
предположительно (Bus error 10)*/
void 		move_forward(t_vars *vars)
{
	double  x;
	double  y;
    int     line;
    int     column;
    
	x = vars->player->x_pos;
	y = vars->player->y_pos;
	x += speed * cos(vars->player->pov);
	y += speed * sin(vars->player->pov);
	x = ceil(x) - x < x - floor(x) ? ceil(x) : floor(x);
	y = ceil(y) - y < y - floor(y) ? ceil(y) : floor(y);
    position_detection((int)(x), (int)(y), &line, &column);
    if (vars->map->map[line][column] != '1')
    {
	    vars->player->x_pos = (int)x;
	    vars->player->y_pos = (int)y;
    }
    put_image(vars);
}

void 		move_backward(t_vars *vars)
{
	double  x;
	double  y;
    int     line;
    int     column;
    
	x = vars->player->x_pos;
	y = vars->player->y_pos;
	x += speed * cos(vars->player->pov + M_PI);
	y += speed * sin(vars->player->pov + M_PI);
	x = ceil(x) - x < x - floor(x) ? ceil(x) : floor(x);
	y = ceil(y) - y < y - floor(y) ? ceil(y) : floor(y);
    position_detection((int)(x), (int)(y), &line, &column);
	if (vars->map->map[line][column] != '1')
    {
	    vars->player->x_pos = (int)x;
	    vars->player->y_pos = (int)y;
    }
	put_image(vars);
}

void 		move_left(t_vars *vars)
{
	double x;
	double y;
    int     line;
    int     column;
	double ray;

	x = vars->player->x_pos;
	y = vars->player->y_pos;
	ray = vars->player->pov - M_PI_2;
	x += speed * cos(ray);
	y += speed * sin(ray);
	x = ceil(x) - x < x - floor(x) ? ceil(x) : floor(x);
	y = ceil(y) - y < y - floor(y) ? ceil(y) : floor(y);
    position_detection((int)(x), (int)(y), &line, &column);
	if (vars->map->map[line][column] != '1')
    {
	    vars->player->x_pos = (int)x;
	    vars->player->y_pos = (int)y;
    }
	put_image(vars);
}

void 		move_right(t_vars *vars)
{
	double x;
	double y;
    int     line;
    int     column;
	double ray;

	x = vars->player->x_pos;
	y = vars->player->y_pos;
	ray = vars->player->pov + M_PI_2;
	x += speed * cos(ray);
	y += speed * sin(ray);
	x = ceil(x) - x < x - floor(x) ? ceil(x) : floor(x);
	y = ceil(y) - y < y - floor(y) ? ceil(y) : floor(y);
    position_detection((int)(x), (int)(y), &line, &column);
	if (vars->map->map[line][column] != '1')
    {
	    vars->player->x_pos = (int)x;
	    vars->player->y_pos = (int)y;
    }
	put_image(vars);
}

void 		rotate_left(t_vars *vars)
{
	vars->player->pov -= rotation_angle;
    if (vars->player->pov >= 2 * M_PI)
		vars->player->pov = vars->player->pov - 2 * M_PI;
	else if (vars->player->pov <= 0)
			vars->player->pov = 2 * M_PI + vars->player->pov;
	put_image(vars);
}

void 		rotate_right(t_vars *vars)
{
	vars->player->pov += rotation_angle;
    if (vars->player->pov >= 2 * M_PI)
	    vars->player->pov = vars->player->pov - 2 * M_PI;
	else if (vars->player->pov <= 0)
		vars->player->pov = 2 * M_PI + vars->player->pov;
	put_image(vars);
}