/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 21:03:45 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/03 17:55:07 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		line_counter()
{

}

double	horizontal_ray_tracer(int x_pos, int y_pos, double ray_angle, char **map)
{
	int			line;
	int			column;
	double		x_cur_pos;
	double		y_cur_pos;
	double		distance;

	distance = 0;
	
	x_cur_pos = x_pos;
	y_cur_pos = y_pos;
	if (ray_angle > M_PI && ray_angle < 2 * M_PI)
	{
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
			column++;
			line += line_counter();
		}
	}
	else if (ray_angle > 0 && ray_angle < M_PI)
	{
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
			column--;
			line += line_counter();
		}
	}
	else if (ray_angle == 3 * M_PI / 2 || ray_angle == M_PI / 2)
	{
		while(map[line][column] != '1')
		{
			y_cur_pos = (ray_angle == M_PI / 2) ? y_cur_pos + 64 : y_cur_pos - 64;
			distance += 64;
		}
	}
	return (distance);
}