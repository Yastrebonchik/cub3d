/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycaster_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 08:38:18 by kcedra            #+#    #+#             */
/*   Updated: 2020/10/12 08:38:19 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		left_half_beg(t_lin_col *lin_col, int x_cur_pos, double *y_cur_pos,
double ray_angle)
{
	int		x_pos;
	double	distance;
	double	y_pos;

	x_pos = x_cur_pos;
	y_pos = *y_cur_pos;
	distance = 0;
	while (x_cur_pos % 64 != 0)
		x_cur_pos--;
	if (ray_angle > M_PI)
	{
		(*y_cur_pos) -= ft_abs(x_pos - x_cur_pos) * (tan(ray_angle - M_PI));
		distance += ft_abs(x_pos - x_cur_pos) / (cos(ray_angle - M_PI));
	}
	else
	{
		(*y_cur_pos) += ft_abs(x_pos - x_cur_pos) * (tan(M_PI - ray_angle));
		distance += ft_abs(x_pos - x_cur_pos) / (cos(M_PI - ray_angle));
	}
	lin_col->column--;
	lin_col->line += line_counter(&y_pos, *y_cur_pos, ray_angle, 0);
	lin_col->distance = distance;
}

double		left_half_end(t_lin_col *lin_col, t_map *map, double *y_cur_pos,
double ray_angle)
{
	double	distance;
	double	y_pos;

	y_pos = *y_cur_pos;
	distance = lin_col->distance;
	while (lin_col->line > 0 && lin_col->column > 0 && lin_col->line <
	map->line_max && (map->map)[lin_col->line][lin_col->column] != '1')
	{
		if (ray_angle > M_PI)
		{
			*y_cur_pos -= 64 * (tan(ray_angle - M_PI));
			distance += 64 / (cos(ray_angle - M_PI));
		}
		else
		{
			*y_cur_pos += 64 * (tan(M_PI - ray_angle));
			distance += 64 / (cos(M_PI - ray_angle));
		}
		lin_col->column--;
		lin_col->line += line_counter(&y_pos, *y_cur_pos, ray_angle, 0);
	}
	return (distance);
}

void		right_half_beg(t_lin_col *lin_col, int x_cur_pos, double *y_cur_pos,
double ray_angle)
{
	int		x_pos;
	double	distance;
	double	y_pos;

	x_pos = x_cur_pos;
	y_pos = *y_cur_pos;
	distance = 0;
	while (x_cur_pos % 64 != 0)
		x_cur_pos++;
	if (ray_angle > 3 * M_PI_2)
	{
		*y_cur_pos -= ft_abs(x_pos - x_cur_pos) * (tan(2 * M_PI - ray_angle));
		distance += ft_abs(x_pos - x_cur_pos) / (cos(2 * M_PI - ray_angle));
	}
	else
	{
		*y_cur_pos += ft_abs(x_pos - x_cur_pos) * (tan(ray_angle));
		distance += ft_abs(x_pos - x_cur_pos) / (cos(ray_angle));
	}
	if (x_cur_pos != x_pos)
		lin_col->column++;
	lin_col->line += line_counter(&y_pos, *y_cur_pos, ray_angle, 0);
	lin_col->distance = distance;
}

double		right_half_end(t_lin_col *lin_col, t_map *map, double *y_cur_pos,
double ray_angle)
{
	double	distance;
	double	y_pos;

	y_pos = *y_cur_pos;
	distance = lin_col->distance;
	while (lin_col->line > 0 && lin_col->line < map->line_max && lin_col->column
	< map->column_max && (map->map)[lin_col->line][lin_col->column] != '1')
	{
		if (ray_angle > 3 * M_PI / 2)
		{
			*y_cur_pos -= 64 * (tan(2 * M_PI - ray_angle));
			distance += 64 / (cos(2 * M_PI - ray_angle));
		}
		else
		{
			*y_cur_pos += 64 * (tan(ray_angle));
			distance += 64 / (cos(ray_angle));
		}
		lin_col->column++;
		lin_col->line += line_counter(&y_pos, *y_cur_pos, ray_angle, 0);
	}
	return (distance);
}
