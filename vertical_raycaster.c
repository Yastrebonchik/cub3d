/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycaster.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:32:39 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/21 12:21:54 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				line_counter(double *y_pos, double y_cur_pos, double ray_angle,
int result)
{
	int		fractional;

	fractional = (int)(*y_pos);
	if ((ray_angle > M_PI && ray_angle < 3 * M_PI_2) ||
	(ray_angle > 3 * M_PI_2 && ray_angle < 2 * M_PI))
	{
		while (fractional > y_cur_pos)
		{
			if (fractional % 64 == 0 && fractional > y_cur_pos)
				result--;
			fractional--;
		}
	}
	else if ((ray_angle > 0 && ray_angle < M_PI_2) ||
	(ray_angle > M_PI_2 && ray_angle < M_PI))
	{
		while (fractional < y_cur_pos)
		{
			if (fractional % 64 == 0 && fractional != (int)(*y_pos))
				result++;
			fractional++;
		}
	}
	*y_pos = y_cur_pos;
	return (result);
}

static double	pi_case(t_lin_col *lin_col, t_map *map, int x_cur_pos)
{
	double	distance;
	int		x_pos;

	distance = 0;
	x_pos = x_cur_pos;
	while (x_cur_pos % 64 != 0)
		x_cur_pos--;
	distance += ft_abs(x_cur_pos - x_pos);
	lin_col->column--;
	while ((map->map)[lin_col->line][lin_col->column] != '1')
	{
		distance += 64;
		lin_col->column--;
	}
	return (distance);
}

static double	zero_case(t_lin_col *lin_col, t_map *map, int x_cur_pos)
{
	double	distance;
	int		x_pos;

	distance = 0;
	x_pos = x_cur_pos;
	while (x_cur_pos % 64 != 0)
		x_cur_pos++;
	distance += ft_abs(x_cur_pos - x_pos);
	if (x_cur_pos != x_pos)
		lin_col->column++;
	while ((map->map)[lin_col->line][lin_col->column] != '1')
	{
		distance += 64;
		lin_col->column++;
	}
	return (distance);
}

double			vertical_raycaster(int x_pos, double y_pos, double ray_angle,
t_map *map)
{
	t_lin_col	lin_col;
	double		y_cur_pos;
	double		distance;

	distance = 0;
	position_detection(x_pos, (int)y_pos, &(lin_col.line), &(lin_col.column));
	y_cur_pos = y_pos;
	if ((ray_angle > M_PI_2 && ray_angle < M_PI) || (ray_angle > M_PI &&
	ray_angle < 3 * M_PI_2))
	{
		left_half_beg(&lin_col, x_pos, &y_cur_pos, ray_angle);
		distance = left_half_end(&lin_col, map, &y_cur_pos, ray_angle);
	}
	else if ((ray_angle > 0 && ray_angle < M_PI_2) || (ray_angle > 3 * M_PI_2
	&& ray_angle < 2 * M_PI))
	{
		right_half_beg(&lin_col, x_pos, &y_cur_pos, ray_angle);
		distance = right_half_end(&lin_col, map, &y_cur_pos, ray_angle);
	}
	else if (ray_angle == M_PI)
		distance = pi_case(&lin_col, map, x_pos);
	else if (ray_angle == 0)
		distance = zero_case(&lin_col, map, x_pos);
	map->coord_y = floor(y_cur_pos);
	return (distance);
}
