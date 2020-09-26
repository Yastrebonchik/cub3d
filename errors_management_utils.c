/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_management_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 20:44:19 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/26 20:44:29 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_resolution(char *text, char res, t_vars *vars)
{
	int resolution;
	int i;
	int x;
	int y;

	i = 0;
	while (ft_isdigit(text[i]) == 1)
		i++;
	mlx_get_screen_size(vars->mlx, &x, &y);
	if (i > 4)
		resolution = (res == 'x') ? x : y;
	else
		resolution = ft_atoi(&(text[0]));
	if (res == 'x' && resolution > x)
		resolution = x;
	if (res == 'y' && resolution > y)
		resolution = y;
	if (resolution == 0)
	{
		ft_putendl_fd("Error\nInvalid resolution config", 1);
		exit(1);
	}
	return (resolution);
}
