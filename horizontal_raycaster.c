/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycaster.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 21:03:45 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/21 12:21:19 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				column_counter(double *x_pos, double x_cur_pos,
double ray_angle, int result)
{
	int		fractional;

	fractional = (int)(*x_pos);
	if ((ray_angle > 0 && ray_angle < M_PI_2) || (ray_angle > 3 * M_PI_2
	&& ray_angle < 2 * M_PI))
	{
		while (fractional < x_cur_pos)
		{
			if (fractional % 64 == 0 && fractional != (int)(*x_pos))
				result++;
			fractional++;
		}
	}
	else if ((ray_angle > M_PI_2 && ray_angle < M_PI) || (ray_angle > M_PI
	&& ray_angle < 3 * M_PI_2))
	{
		while (fractional > x_cur_pos)
		{
			if (fractional % 64 == 0)
				result--;
			fractional--;
		}
	}
	*x_pos = x_cur_pos;
	return (result);
}

static double	three_m_pi_case(t_lin_col *lin_col, t_map *map, int y_cur_pos)
{
	double	distance;
	int		y_pos;

	distance = 0;
	y_pos = y_cur_pos;
	while (y_cur_pos % 64 != 0)
		y_cur_pos--;
	distance += ft_abs(y_cur_pos - y_pos);
	lin_col->line--;
	while ((map->map)[lin_col->line][lin_col->column] != '1')
	{
		distance += 64;
		lin_col->line--;
	}
	return (distance);
}

static double	m_pi_case(t_lin_col *lin_col, t_map *map, int y_cur_pos)
{
	double	distance;
	int		y_pos;

	distance = 0;
	y_pos = y_cur_pos;
	while (y_cur_pos % 64 != 0)
		y_cur_pos++;
	distance += ft_abs(y_cur_pos - y_pos);
	if (y_cur_pos != y_pos)
		lin_col->line++;
	while ((map->map)[lin_col->line][lin_col->column] != '1')
	{
		distance += 64;
		lin_col->line++;
	}
	return (distance);
}

double			horizontal_raycaster(double x_pos, int y_pos, double ray_angle,
t_map *map)
{
	t_lin_col	lin_col;
	double		x_cur_pos;
	double		distance;

	distance = 0;
	position_detection((int)x_pos, y_pos, &(lin_col.line), &(lin_col.column));
	x_cur_pos = x_pos;
	if ((ray_angle > M_PI && ray_angle < 3 * M_PI_2) || (ray_angle > 3 * M_PI_2
	&& ray_angle < 2 * M_PI))
	{
		up_half_beg(&lin_col, y_pos, &x_cur_pos, ray_angle);
		distance = up_half_end(&lin_col, map, &x_cur_pos, ray_angle);
	}
	else if ((ray_angle > 0 && ray_angle < M_PI_2) || (ray_angle > M_PI_2
	&& ray_angle < M_PI))
	{
		down_half_beg(&lin_col, y_pos, &x_cur_pos, ray_angle);
		distance = down_half_end(&lin_col, map, &x_cur_pos, ray_angle);
	}
	else if (ray_angle == 3 * M_PI_2)
		distance = three_m_pi_case(&lin_col, map, y_pos);
	else if (ray_angle == M_PI_2)
		distance = m_pi_case(&lin_col, map, y_pos);
	map->coord_x = floor(x_cur_pos);
	return (distance);
}
