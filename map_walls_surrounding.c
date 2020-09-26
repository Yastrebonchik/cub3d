/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls_surrounding.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:47:05 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/26 19:47:08 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_first_and_last(char **map, int line, int *column)
{
	while (map[line][*column] != '\0')
	{
		if (map[line][*column] != '1' && map[line][*column] != ' ')
		{
			ft_putendl_fd("Error\nMap is not surrounded by walls", 1);
			exit(1);
		}
		(*column)++;
	}
}

static void	check_surrounding(char **map, char side, int line, int *column)
{
	int flag;

	flag = 0;
	if (map[line][*column] == '0' || map[line][*column] == '2' ||
		map[line][*column] == side)
	{
		if ((map[line + 1][*column] != '0' && map[line + 1][*column] != '2'
		&& map[line + 1][*column] != '1' && map[line + 1][*column] != side))
			flag = 1;
		if ((map[line][*column + 1] != '0' && map[line][*column + 1] != '2'
		&& map[line][*column + 1] != '1' && map[line][*column + 1] != side))
			flag = 1;
		if ((map[line - 1][*column] != '0' && map[line - 1][*column] != '2'
		&& map[line - 1][*column] != '1' && map[line - 1][*column] != side))
			flag = 1;
		if ((map[line][*column - 1] != '0' && map[line][*column - 1] != '2'
		&& map[line][*column - 1] != '1' && map[line][*column - 1] != side))
			flag = 1;
	}
	(*column)++;
	if (flag == 1)
	{
		ft_putendl_fd("Error\nMap is not surrounded by walls", 1);
		exit(1);
	}
}

void		walls_surrounding(char **map, char side)
{
	int	line;
	int column;

	line = 0;
	column = 0;
	check_first_and_last(map, line, &column);
	line++;
	while (map[line + 1] != NULL)
	{
		column = 0;
		while (map[line][column] != '\0')
		{
			check_surrounding(map, side, line, &column);
		}
		line++;
	}
	column = 0;
	check_first_and_last(map, line, &column);
}
