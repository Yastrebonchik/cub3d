/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:29:24 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/25 23:11:43 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		text_join_n(char **text, char **line, int gnl)
{
	char	*collat;
	int		i;

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

double		min_of_2_cub(double a, double b, t_vars *vars)
{
	if (a < b)
		vars->flag = 'E';
	else
		vars->flag = 'N';
	return ((a < b) ? a : b);
}

void		check_side_of_world(t_vars *vars, double current_ray)
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
