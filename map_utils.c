/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 17:09:43 by alexander         #+#    #+#             */
/*   Updated: 2020/09/16 17:10:10 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		ft_putendl_fd(map[i], 1);
		i++;
	}
}

void		limit_counter(t_map *map)
{
	int 	line;
	int 	column;
	int 	max;

	line = 0;
	column = 0;
	while (map->map[line] != NULL)
	{
		max = 0;
		while (map->map[line][max] != '\0')
			max++;
		if (max > column)
			column = max;
		line++;
	}
	map->line_max = line;
	map->column_max = column;
}

void 		position_detection(int x, int y, int *line, int *column)
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