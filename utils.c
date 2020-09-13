/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:29:24 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/05 13:38:14 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		text_join_n(char **text, char **line, int gnl)
{
	char    *collat;
	int     i;

	i = 0;
	collat = ft_strjoin(*text, *line);
	free(*text);
	*text = ft_strdup(collat);
	free(collat);
	collat = ft_strjoin(*text, "\n");
	free(*text);
	*text = ft_strdup(collat);
	free(collat);
	free(*line);
	if (gnl == 0)
	{
		while ((*text)[i] != '\0')
			i++;
		(*text)[i - 1] = '\0';
	}
}

static int	get_digit(char character)
{
	int	digit;

	if (character == 'F')
			digit = 15;
	else if (character == 'E')
			digit = 14;
	else if (character == 'D')
			digit = 13;
	else if (character == 'C')
			digit = 12;
	else if (character == 'B')
			digit = 11;
	else if (character == 'A')
			digit = 10;
	else
			digit = character - '0';
	return (digit);
}

int			atoi_color_base_16(char *color)
{
	int	i;
	int	decimal;
	int result;
	int	digit;

	result = 0;
	decimal = 1;
	i = (int)ft_strlen(color) - 1;
	while (i != -1)
	{
		digit = get_digit(color[i]);
		result += digit * decimal;
		decimal *= 16;
		i--;
	}
	return (result);
}

void		pars_init(t_pars *pars)
{
	pars->flag = 0;
	pars->res_x = -1;
	pars->res_y = -1;
	pars->north_texture = NULL;
	pars->south_texture = NULL;
	pars->west_texture = NULL;
	pars->east_texture = NULL;
	pars->sprite_texture = NULL;
	pars->floor_color = NULL;
	pars->ceiling_color = NULL;
	pars->map = NULL;
}

int			check_validity(t_pars *pars)
{
	if ((pars->res_x != -1) && (pars->res_y != -1)
	&& (pars->north_texture != NULL) && (pars->south_texture != NULL)
	&& (pars->west_texture != NULL) && (pars->east_texture != NULL)
	&& (pars->sprite_texture != NULL) && (pars->floor_color != NULL)
	&& (pars->ceiling_color != NULL))
		return (1);
	else
		return (0);	
}

double		ft_abs(double a)
{
	if (a < 0)
		a = a * (-1);
	return (a);
}

double		min_of_2(double a, double b)
{
	return ((a < b) ? a : b);
}

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

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int				my_mlx_get_color(t_data *data, int x, int y)
{
	char 	*dst;
	int 	color;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}