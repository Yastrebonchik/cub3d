/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:29:24 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/15 23:36:36 by alexander        ###   ########.fr       */
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

double		min_of_2_cub(double a, double b, t_vars * vars)
{
	if (a < b)
		vars->flag = 'E';
	else
		vars->flag = 'N';
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

void			put_textures(t_vars *vars)
{
	t_data	*north_texture;
	t_data	*south_texture;
	t_data	*west_texture;
	t_data	*east_texture;
	
	north_texture = (t_data*)malloc(sizeof(t_data));
	south_texture = (t_data*)malloc(sizeof(t_data));
	east_texture = (t_data*)malloc(sizeof(t_data));
	west_texture = (t_data*)malloc(sizeof(t_data));
	(*north_texture).img = mlx_xpm_file_to_image(vars->mlx,
	vars->pars->north_texture, &((*north_texture).width), &((*north_texture).height));
	(*south_texture).img = mlx_xpm_file_to_image(vars->mlx,
	vars->pars->south_texture, &((*south_texture).width), &((*south_texture).height));
	(*east_texture).img = mlx_xpm_file_to_image(vars->mlx,
	vars->pars->east_texture, &((*east_texture).width), &((*east_texture).height));
	(*west_texture).img = mlx_xpm_file_to_image(vars->mlx,
	vars->pars->west_texture, &((*west_texture).width), &((*west_texture).height));
	vars->north_texture = north_texture;
	vars->south_texture = south_texture;
	vars->east_texture = east_texture;
	vars->west_texture = west_texture;
	if ((*north_texture).img == NULL || (*south_texture).img == NULL
	|| (*east_texture).img == NULL || (*west_texture).img == NULL)
	{
		ft_putendl_fd("Error\nInvalid texture path file", 1);
		exit(1);
	}
	vars->north_texture->addr = mlx_get_data_addr(vars->north_texture->img,
	&(vars->north_texture->bits_per_pixel), &(vars->north_texture->line_length), &vars->north_texture->endian);
	vars->south_texture->addr = mlx_get_data_addr(vars->south_texture->img,
	&(vars->south_texture->bits_per_pixel), &(vars->south_texture->line_length), &(vars->south_texture->endian));
	vars->east_texture->addr = mlx_get_data_addr(vars->east_texture->img,
	&(vars->east_texture->bits_per_pixel), &(vars->east_texture->line_length), &(vars->east_texture->endian));
	vars->west_texture->addr = mlx_get_data_addr(vars->west_texture->img,
	&(vars->west_texture->bits_per_pixel), &(vars->west_texture->line_length), &(vars->west_texture->endian));
}

void            check_side_of_world(t_vars *vars, double current_ray)
{
    if (vars->flag == 'E')
    {
        if (current_ray >= (M_PI_2) && current_ray <= 3 * M_PI_2)
            vars->flag = 'W';
    }
    else
    {
        if (current_ray > 0 && current_ray < M_PI)
            vars->flag = 'S';
    }
}