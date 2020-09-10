/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycaster.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 21:03:45 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/05 12:53:39 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void position_detection(int x, int y, int *line, int *column)
{
	int x_cur_pos;
	int y_cur_pos;

	x_cur_pos = 0;
	y_cur_pos = 0;
	*line = 0;
	*column = 0;
	while (x_cur_pos != x)
	{
		x_cur_pos++;
		if (x_cur_pos % 64 == 0)
			(*column)++;
	}
	while (y_cur_pos != y)
	{
		y_cur_pos++;
		if (y_cur_pos % 64 == 0)
			(*line)++;
	}
}

static int	column_counter(double *x_pos, double x_cur_pos, double ray_angle)
{
	int		result;
	int 	fractional;
	double	integral;
	double	integral_int;

	result = 0;
	integral = modf(*x_pos, &integral_int);
	fractional = (int)integral_int;
	if ((ray_angle > 0 && ray_angle < M_PI_2) || (ray_angle > 3 * M_PI_2 && ray_angle < 2 * M_PI))
	{
		while (fractional < x_cur_pos)
		{
			if (fractional % 64 == 0 && fractional != (int)integral_int)
				result++;
			fractional++;
		}
	}
	else if ((ray_angle > M_PI_2 && ray_angle < M_PI) || (ray_angle > M_PI && ray_angle < 3 * M_PI_2))
	{
		while (fractional > x_cur_pos)
		{
			if (fractional % 64 == 0 && fractional > x_cur_pos)
				result--;
			fractional--;
		}
	}
	*x_pos = x_cur_pos;
	return (result);
}

double		horizontal_raycaster(double x_pos, int y_pos, double ray_angle, t_map *map)
{
	int 		line;
	int 		column;
	int			y_cur_pos;
	double		x_cur_pos;
	double		distance;

	distance = 0;
	position_detection(x_pos, y_pos, &line, &column);
	x_cur_pos = x_pos;
	y_cur_pos = y_pos;
	if ((ray_angle > M_PI && ray_angle < 3 * M_PI_2) || (ray_angle > 3 * M_PI_2 && ray_angle < 2 * M_PI))
	{
		while (y_cur_pos % 64 != 0)
			y_cur_pos--;
		if (ray_angle > 3 * M_PI / 2)
		{
			x_cur_pos += ft_abs(y_pos - y_cur_pos) / (tan(2 * M_PI - ray_angle));
			distance += ft_abs(y_pos - y_cur_pos) / (sin(2 * M_PI - ray_angle));
		}
		else
		{
			x_cur_pos -= ft_abs(y_pos - y_cur_pos) / (tan(ray_angle - M_PI));
			distance += ft_abs(y_pos - y_cur_pos) / (sin(ray_angle - M_PI));
		}
		//if (y_cur_pos != y_pos)
			line--;
		column += column_counter(&x_pos, x_cur_pos, ray_angle);
		while(column > 0 && line > 0 && column < map->column_max && (map->map)[line][column] != '1')
		{
			y_cur_pos -= 64;
			if (ray_angle > 3 * M_PI / 2)
			{
				x_cur_pos += 64 / (tan(2 * M_PI - ray_angle));
				distance += 64 / (sin(2 * M_PI - ray_angle));
			}
			else
			{
				x_cur_pos -= 64 / (tan(ray_angle - M_PI));
				distance += 64 / (sin(ray_angle - M_PI));
			}
			line--;
			column += column_counter(&x_pos, x_cur_pos, ray_angle);
		}
	}
	else if ((ray_angle > 0 && ray_angle < M_PI_2) || (ray_angle > M_PI_2 && ray_angle < M_PI))
	{
		while (y_cur_pos % 64 != 0)
			y_cur_pos++;
		if (ray_angle > M_PI / 2)
		{
			x_cur_pos -= ft_abs(y_pos - y_cur_pos) / (tan(M_PI - ray_angle));
			distance += ft_abs(y_pos - y_cur_pos) / (sin(M_PI - ray_angle));
		}
		else
		{
			x_cur_pos += ft_abs(y_pos - y_cur_pos) / (tan(ray_angle));
			distance += ft_abs(y_pos - y_cur_pos) / (sin(ray_angle));
		}
		if (y_cur_pos != y_pos)
			line++;
		column += column_counter(&x_pos, x_cur_pos, ray_angle);
		while(column > 0 && column < map->column_max && line > 0 && line < map->line_max && (map->map)[line][column] != '1')
		{
			y_cur_pos += 64;
			if (ray_angle > M_PI / 2)
			{
				x_cur_pos -= 64 / (tan(M_PI - ray_angle));
				distance += 64 / (sin(M_PI - ray_angle));
			}
			else
			{
				x_cur_pos += 64 / (tan(ray_angle));
				distance += 64 / (sin(ray_angle));
			}
			line++;
			column += column_counter(&x_pos, x_cur_pos, ray_angle);
		}
	}
	else if (ray_angle == 3 * M_PI_2)
	{
		//printf("I'm here\n");
		while (y_cur_pos % 64 != 0)
			y_cur_pos--;
		distance += ft_abs(y_cur_pos - y_pos);
		if (y_cur_pos != y_pos)
			line--;
		while((map->map)[line][column] != '1')
		{
			//printf("Map line = %d & Map column = %d\n", line, column);
			y_cur_pos -= 64;
			distance += 64;
			line--;
		}
	}
	else if (ray_angle == M_PI_2)
	{
		while (y_cur_pos % 64 != 0)
			y_cur_pos++;
		distance += ft_abs(y_cur_pos - y_pos);
		//if (y_cur_pos != y_pos || y_pos == 0)
			line++;
		while((map->map)[line][column] != '1')
		{
			y_cur_pos += 64;
			distance += 64;
			line++;
		}
	}
	return (distance);
}