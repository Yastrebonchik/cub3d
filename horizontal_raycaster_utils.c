/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycaster_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 10:30:36 by kcedra            #+#    #+#             */
/*   Updated: 2020/10/14 10:30:38 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		up_half_beg(t_lin_col *lin_col, int y_cur_pos, double *x_cur_pos,
double ray_angle)
{
	int		y_pos;
	double	distance;
	double	x_pos;

	x_pos = *x_cur_pos;
	y_pos = y_cur_pos;
	distance = 0;
	while (y_cur_pos % 64 != 0)
		y_cur_pos--;
	if (ray_angle > 3 * M_PI / 2)
	{
		*x_cur_pos += ft_abs(y_pos - y_cur_pos) / (tan(2 * M_PI - ray_angle));
		distance += ft_abs(y_pos - y_cur_pos) / (sin(2 * M_PI - ray_angle));
	}
	else
	{
		*x_cur_pos -= ft_abs(y_pos - y_cur_pos) / (tan(ray_angle - M_PI));
		distance += ft_abs(y_pos - y_cur_pos) / (sin(ray_angle - M_PI));
	}
	lin_col->line--;
	lin_col->column += column_counter(&x_pos, *x_cur_pos, ray_angle, 0);
	lin_col->distance = distance;
}

double		up_half_end(t_lin_col *lin_col, t_map *map, double *x_cur_pos,
double ray_angle)
{
	double	distance;
	double	x_pos;

	x_pos = *x_cur_pos;
	distance = lin_col->distance;
	while (lin_col->column > 0 && lin_col->line > 0 && lin_col->column
	< map->column_max && (map->map)[lin_col->line][lin_col->column] != '1')
	{
		if (ray_angle > 3 * M_PI / 2)
		{
			*x_cur_pos += 64 / (tan(2 * M_PI - ray_angle));
			distance += 64 / (sin(2 * M_PI - ray_angle));
		}
		else
		{
			*x_cur_pos -= 64 / (tan(ray_angle - M_PI));
			distance += 64 / (sin(ray_angle - M_PI));
		}
		lin_col->line--;
		lin_col->column += column_counter(&x_pos, *x_cur_pos, ray_angle, 0);
	}
	return (distance);
}

void		down_half_beg(t_lin_col *lin_col, int y_cur_pos, double *x_cur_pos,
double ray_angle)
{
	int		y_pos;
	double	distance;
	double	x_pos;

	x_pos = *x_cur_pos;
	y_pos = y_cur_pos;
	distance = 0;
	while (y_cur_pos % 64 != 0)
		y_cur_pos++;
	if (ray_angle > M_PI / 2)
	{
		*x_cur_pos -= ft_abs(y_pos - y_cur_pos) / (tan(M_PI - ray_angle));
		distance += ft_abs(y_pos - y_cur_pos) / (sin(M_PI - ray_angle));
	}
	else
	{
		*x_cur_pos += ft_abs(y_pos - y_cur_pos) / (tan(ray_angle));
		distance += ft_abs(y_pos - y_cur_pos) / (sin(ray_angle));
	}
	if (y_cur_pos != y_pos)
		lin_col->line++;
	lin_col->column += column_counter(&x_pos, *x_cur_pos, ray_angle, 0);
	lin_col->distance = distance;
}

double		down_half_end(t_lin_col *lin_col, t_map *map, double *x_cur_pos,
double ray_angle)
{
	double	distance;
	double	x_pos;

	x_pos = *x_cur_pos;
	distance = lin_col->distance;
	while (lin_col->column > 0 && lin_col->column < map->column_max &&
	lin_col->line > 0 && lin_col->line < map->line_max &&
	(map->map)[lin_col->line][lin_col->column] != '1')
	{
		if (ray_angle > M_PI / 2)
		{
			*x_cur_pos -= 64 / (tan(M_PI - ray_angle));
			distance += 64 / (sin(M_PI - ray_angle));
		}
		else
		{
			*x_cur_pos += 64 / (tan(ray_angle));
			distance += 64 / (sin(ray_angle));
		}
		lin_col->line++;
		lin_col->column += column_counter(&x_pos, *x_cur_pos, ray_angle, 0);
	}
	return (distance);
}
