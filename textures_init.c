/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 08:03:25 by kcedra            #+#    #+#             */
/*   Updated: 2020/10/12 08:03:47 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		get_data_addr(t_vars *vars)
{
	vars->north_texture->addr = mlx_get_data_addr(vars->north_texture->img,
	&(vars->north_texture->bits_per_pixel), &(vars->north_texture->line_length),
	&vars->north_texture->endian);
	vars->south_texture->addr = mlx_get_data_addr(vars->south_texture->img,
	&(vars->south_texture->bits_per_pixel), &(vars->south_texture->line_length),
	&(vars->south_texture->endian));
	vars->east_texture->addr = mlx_get_data_addr(vars->east_texture->img,
	&(vars->east_texture->bits_per_pixel), &(vars->east_texture->line_length),
	&(vars->east_texture->endian));
	vars->west_texture->addr = mlx_get_data_addr(vars->west_texture->img,
	&(vars->west_texture->bits_per_pixel), &(vars->west_texture->line_length),
	&(vars->west_texture->endian));
	vars->sprite_texture->addr = mlx_get_data_addr(vars->sprite_texture->img,
	&(vars->sprite_texture->bits_per_pixel),
	&(vars->sprite_texture->line_length), &(vars->sprite_texture->endian));
}

static void		textures_img_first(t_data *north_texture,
t_data *south_texture, t_data *west_texture, t_vars *vars)
{
	(*north_texture).img = mlx_xpm_file_to_image(vars->mlx, vars->
	pars->north_texture, &((*north_texture).width), &((*north_texture).height));
	(*south_texture).img = mlx_xpm_file_to_image(vars->mlx, vars->
	pars->south_texture, &((*south_texture).width), &((*south_texture).height));
	(*west_texture).img = mlx_xpm_file_to_image(vars->mlx, vars->
	pars->west_texture, &((*west_texture).width), &((*west_texture).height));
	if ((*north_texture).img == NULL || (*south_texture).img == NULL
	|| (*west_texture).img == NULL)
	{
		ft_putendl_fd("Error\nInvalid texture path file", 1);
		exit(1);
	}
	vars->north_texture = north_texture;
	vars->south_texture = south_texture;
	vars->west_texture = west_texture;
}

static void		textures_img_second(t_data *east_texture,
t_data *sprite_texture, t_vars *vars)
{
	(*sprite_texture).img = mlx_xpm_file_to_image(vars->mlx, vars->
	pars->sprite_texture, &((*sprite_texture).width),
	&((*sprite_texture).height));
	(*east_texture).img = mlx_xpm_file_to_image(vars->mlx, vars->
	pars->east_texture, &((*east_texture).width), &((*east_texture).height));
	if ((*east_texture).img == NULL || (*sprite_texture).img == NULL)
	{
		ft_putendl_fd("Error\nInvalid texture path file", 1);
		exit(1);
	}
	vars->east_texture = east_texture;
	vars->sprite_texture = sprite_texture;
}

void			put_textures(t_vars *vars)
{
	t_data	*north_texture;
	t_data	*south_texture;
	t_data	*west_texture;
	t_data	*east_texture;
	t_data	*sprite_texture;

	if (!(north_texture = (t_data*)malloc(sizeof(t_data))) ||
	!(south_texture = (t_data*)malloc(sizeof(t_data))) ||
	!(east_texture = (t_data*)malloc(sizeof(t_data))) ||
	!(west_texture = (t_data*)malloc(sizeof(t_data))) ||
	!(sprite_texture = (t_data*)malloc(sizeof(t_data))))
	{
		ft_putendl_fd("Error\nMalloc error", 1);
		exit(1);
	}
	textures_img_first(north_texture, south_texture, west_texture, vars);
	textures_img_second(east_texture, sprite_texture, vars);
	get_data_addr(vars);
}
