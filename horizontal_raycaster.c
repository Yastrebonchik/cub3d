/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raytracer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 21:03:45 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/04 17:46:52 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	column_counter(double *x_pos, double x_cur_pos, double ray_angle)
{
	int		result;
	double	integral;
	double	fractional;
	double	distance;
	int		integral_int;

	result = 0;
	integral = modf(*x_pos, &fractional);
	integral_int = (int)integral;
	if ((ray_angle > 0 && ray_angle < M_PI_2) || (ray_angle > 3 * M_PI_2 && ray_angle < 2 * M_PI))
	{
		while (integral_int + fractional < x_cur_pos)
		{
			integral_int++;
			if (integral_int % 64 == 0)
				result++;
		}
	}
	else if ((ray_angle > M_PI_2 && ray_angle < M_PI) || (ray_angle > M_PI && ray_angle < 3 * M_PI_2))
	{
		while (integral_int + fractional > x_cur_pos)
		{
			integral_int--;
			if (integral_int % 64 == 0)
				result--;
		}
	}
	*x_pos = x_cur_pos;
	return (result);
}

double		horizontal_ray_tracer(double x_pos, int y_pos, double ray_angle, char **map, int line, int column)
{
	int			y_cur_pos;
	double		x_cur_pos;
	double		distance;

	distance = 0;
	
	x_cur_pos = x_pos;
	y_cur_pos = y_pos;
	if ((ray_angle > M_PI && ray_angle < 3 * M_PI_2) || (ray_angle > 3 * M_PI_2 && ray_angle < 2 * M_PI))
	{
		while (y_cur_pos % 64 != 0)
			y_cur_pos--;
		if (ray_angle > 3 * M_PI / 2)
		{
			x_cur_pos += ft_abs(y_pos - y_cur_pos) * (tan(ray_angle) * (-1));
			distance += ft_abs(y_pos - y_cur_pos) / (sin(2 * M_PI - ray_angle));
		}
		else
		{
			x_cur_pos -= ft_abs(y_pos - y_cur_pos) * (tan(ray_angle));
			distance += ft_abs(y_pos - y_cur_pos) / (sin(ray_angle - M_PI));
		}
		if (y_cur_pos != y_pos)
			line--;
		line += column_counter(&x_pos, x_cur_pos, ray_angle);
		while(map[line][column] != '1')
		{
			y_cur_pos -= 64;
			if (ray_angle > 3 * M_PI / 2)
			{
				x_cur_pos += 64 * (tan(ray_angle) * (-1));
				distance += 64 / (sin(2 * M_PI - ray_angle));
			}
			else
			{
				x_cur_pos -= 64 * (tan(ray_angle));
				distance += 64 / (sin(ray_angle - M_PI));
			}
			line--;
			column += column_counter(&x_pos, x_cur_pos, ray_angle);
		}
	}
	else if ((ray_angle > 0 && ray_angle < M_PI_2) || ( ray_angle > M_PI_2 && ray_angle < M_PI))
	{
		while (y_cur_pos % 64 != 0)
			y_cur_pos++;
		if (ray_angle > M_PI / 2)
		{
			x_cur_pos -= ft_abs(y_pos - y_cur_pos) * (tan(ray_angle) * (-1));
			distance += ft_abs(y_pos - y_cur_pos) / (sin(M_PI - ray_angle));
		}
		else
		{
			x_cur_pos += ft_abs(y_pos - y_cur_pos) * (tan(ray_angle));
			distance += ft_abs(y_pos - y_cur_pos) / (sin(ray_angle));
		}
		if (y_cur_pos != y_pos)
			line++;
		column += column_counter(&x_pos, x_cur_pos, ray_angle);
		while(map[line][column] != '1')
		{
			y_cur_pos += 64;
			if (ray_angle > M_PI / 2)
			{
				x_cur_pos -= 64 * (tan(ray_angle) * (-1));
				distance += 64 / (sin(M_PI - ray_angle));
			}
			else
			{
				x_cur_pos += 64 * (tan(ray_angle));
				distance += 64 / (sin(ray_angle));
			}
			line++;
			column += column_counter(&x_pos, x_cur_pos, ray_angle);
		}
	}
	else if (ray_angle == 3 * M_PI / 2)
	{
		while (y_cur_pos % 64 != 0)
			y_cur_pos--;
		distance += ft_abs(y_cur_pos - y_pos);
		if (y_cur_pos != y_pos)
			line--;
		while(map[line][column] != '1')
		{
			y_cur_pos -= 64;
			distance += 64;
		}
		line--;
	}
	else if (ray_angle == M_PI / 2)
	{
		while (y_cur_pos % 64 != 0)
			y_cur_pos++;
		distance += ft_abs(y_cur_pos - y_pos);
		if (y_cur_pos != y_pos)
			line++;
		while(map[line][column] != '1')
		{
			y_cur_pos += 64;
			distance += 64;
		}
		line++;
	}
	return (distance);
}