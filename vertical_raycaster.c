/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycaster.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:32:39 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/14 01:56:51 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	line_counter(double *y_pos, double y_cur_pos, double ray_angle)
{
	int		result;
	int 	fractional;

	result = 0;
	fractional = (int)(*y_pos);
	if ((ray_angle > M_PI && ray_angle < 3 * M_PI_2) || (ray_angle > 3 * M_PI_2 && ray_angle < 2 * M_PI))
	{
		while (fractional > y_cur_pos)
		{
			if (fractional % 64 == 0 && fractional > y_cur_pos)
				result--;
			fractional--;
		}
	}
	else if ((ray_angle > 0 && ray_angle < M_PI_2) || ( ray_angle > M_PI_2 && ray_angle < M_PI))
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

double		vertical_raycaster(int x_pos, double y_pos, double ray_angle, t_map *map)
{
	int 		line;
	int 		column;
	int			x_cur_pos;
	double		y_cur_pos;
	double		distance;

	distance = 0;
	position_detection(x_pos, y_pos, &line, &column);
	x_cur_pos = x_pos;
	y_cur_pos = y_pos;
	if ((ray_angle > M_PI_2 && ray_angle < M_PI) || (ray_angle > M_PI && ray_angle < 3 * M_PI_2))
	{
		while (x_cur_pos % 64 != 0)
			x_cur_pos--;
		if (ray_angle > M_PI)
		{
			y_cur_pos -= ft_abs(x_pos - x_cur_pos) * (tan(ray_angle - M_PI));
			distance += ft_abs(x_pos - x_cur_pos) / (cos(ray_angle - M_PI));
		}
		else
		{
			y_cur_pos += ft_abs(x_pos - x_cur_pos) * (tan(M_PI - ray_angle));
			distance += ft_abs(x_pos - x_cur_pos) / (cos(M_PI - ray_angle));
		}
		column--;
		line += line_counter(&y_pos, y_cur_pos, ray_angle);
		while(line > 0 && column > 0 && line < map->line_max && (map->map)[line][column] != '1')
		{
			x_cur_pos -= 64;
			if (ray_angle > M_PI)
			{
				y_cur_pos -= 64 * (tan(ray_angle - M_PI));
				distance += 64 / (cos(ray_angle - M_PI));
			}
			else
			{
				y_cur_pos += 64 * (tan(M_PI - ray_angle));
				distance += 64 / (cos(M_PI - ray_angle));
			}
			column--;
			line += line_counter(&y_pos, y_cur_pos, ray_angle);
		}
	}
	else if ((ray_angle > 0 && ray_angle < M_PI_2) || (ray_angle > 3 * M_PI_2 && ray_angle < 2 * M_PI))
	{
		while (x_cur_pos % 64 != 0)
			x_cur_pos++;
		if (ray_angle > 3 * M_PI_2)
		{
			y_cur_pos -= ft_abs(x_pos - x_cur_pos) * (tan(2 * M_PI - ray_angle));
			distance += ft_abs(x_pos - x_cur_pos) / (cos(2 * M_PI - ray_angle));
		}
		else
		{
			y_cur_pos += ft_abs(x_pos - x_cur_pos) * (tan(ray_angle));
			distance += ft_abs(x_pos - x_cur_pos) / (cos(ray_angle));
		}
		if (x_cur_pos != x_pos)
			column++;
		line += line_counter(&y_pos, y_cur_pos, ray_angle);
		while(line > 0 && line < map->line_max && column < map->column_max && (map->map)[line][column] != '1')
		{
			x_cur_pos += 64;
			if (ray_angle > 3 * M_PI / 2)
			{
				y_cur_pos -= 64 * (tan(2 * M_PI - ray_angle));
				distance += 64 / (cos(2 * M_PI - ray_angle));
			}
			else
			{
				y_cur_pos += 64 * (tan(ray_angle));
				distance += 64 / (cos(ray_angle));
			}
			column++;
			line += line_counter(&y_pos, y_cur_pos, ray_angle);
		}
	}
	else if (ray_angle == M_PI)
	{
		while (x_cur_pos % 64 != 0)
			x_cur_pos--;
		distance += ft_abs(x_cur_pos - x_pos);
			column--;
		while((map->map)[line][column] != '1')
		{
			x_cur_pos -= 64;
			distance += 64;
			column--;
		}
	}
	else if (ray_angle == 0)
	{
		while (x_cur_pos % 64 != 0)
			x_cur_pos++;
		distance += ft_abs(x_cur_pos - x_pos);
		if (x_cur_pos != x_pos)
			column++;
		while((map->map)[line][column] != '1')
		{
			x_cur_pos += 64;
			distance += 64;
			column++;
		}
	}
	map->coord_y = floor(y_cur_pos);
	return (distance);
}