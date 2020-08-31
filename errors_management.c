/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 17:58:07 by kcedra            #+#    #+#             */
/*   Updated: 2020/08/27 20:03:12 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			color_error_management(char *text, t_pars *pars, int i)
{
	int		flag;
	char	type;

	flag = 0;
	if (text[i] != 'F' && text[i] != 'C')
		flag = 1;
	type = (text[i] == 'F') ? 'F' : 'C';
	i++;
	while (text[i] == ' ')
		i++;
	i = itoa_color_base_16(text, i, pars, type);
	if (i == -1)
	{
		flag = 1;
		i++;
	}
	while (text[i] == ' ')
		i++;
	if (text[i] != '\n')
		flag = 1;
	if (flag == 1)
		ft_putendl_fd("Error\nInvalid color config", 1);
	return (flag);
}

int			resolution_error_managemnt(char *text, t_pars *pars)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (text[i] != 'R' || text[++i] != ' ')
		flag = 1;
	while (text[i] == ' ')
		i++;
	pars->res_x = ft_atoi(&text[i]);
	while (ft_isdigit(text[i]) == 1)
		i++;
	flag = (text[i] != ' ') ? 1 : flag;
	i++;
	while (text[i] == ' ')
		i++;
	pars->res_y = ft_atoi(&text[i]);
	while (ft_isdigit(text[i]) == 1)
		i++;
	while (text[i] == ' ')
		i++;
	flag = (text[i] != '\n') ? 1 : flag;
	if (flag == 1)
		ft_putendl_fd("Error\nInvalid resolution config", 1);
	return (flag);
}

int			file_error_management(int gnl, char *filename)
{
	int	i;

	i = 0;
	if (gnl == -1 || gnl == 0)
	{
		ft_putendl_fd("Error\nInvalid file", 1);
		return (1);
	}
	while (filename[i] != '.' && filename[i] != '\0')
		i++;
	if (filename[i] != '.' && filename[i + 1] != 'c' &&
	filename[i + 2] != 'u' && filename[i + 3] != 'b')
	{
		ft_putendl_fd("Error\nWrong file format", 1);
		return (1);
	}
	else
		i += 4;
	if (filename[i] != '\0')
	{
		ft_putendl_fd("Error\nWrong file format", 1);
		return (1);
	}
	return (0);
}

static int	detect_function(char *text, int i, t_pars *pars)
{
	int	flag;

	flag = 0;
	if (text[i] == 'R')
		flag = resolution_error_managemnt(&(text[i]), pars);
	else if (text[i] == 'N')
		flag = north_texture(text, pars, i);
	else if (text[i] == 'S' && text[i + 1] == 'O')
		flag = south_texture(text, pars, i);
	else if (text[i] == 'W')
		flag = west_texture(text, pars, i);
	else if (text[i] == 'E')
		flag = east_texture(text, pars, i);
	else if (text[i] == 'S')
		flag = sprite_texture(text, pars, i);
	else if (text[i] == 'F' || text[i] == 'C')
		flag = color_error_management(text, pars, i);
	else if (text[i] != '\0')
	{
		flag = 1;
		ft_putendl_fd("Error\nInvalid config", 1);
	}
	return ((flag == 1) ? 1 : 0);
}

int			args_error_management(char *text, t_pars *pars)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (text[i] != '1' && text[i] != '2' && text[i] != '\0')
	{
		while (text[i] == '\n' || text[i] == ' ')
			i++;
		flag = detect_function(text, i, pars);
		if (flag == 1)
		{
			//printf("res_x = %d\nres_y = %d\nnorth_texture - %s\nsouth_texture - %s\neast_texture - %s\nwest_texture - %s\nsprite_texture - %s\nfloor_color = %s\nceiling_color= %s\n", 
	//pars->res_x, pars->res_y, pars->north_texture, pars->south_texture, pars->east_texture, pars->west_texture, pars->sprite_texture, pars->floor_color, pars->ceiling_color);
			return (1);
		}
		while (text[i] != '\0' && text[i] != '\n')
			i++;
		if (check_validity(pars) == 1)
		{
			printf("I'm here\n");
			break;
		}
	}
	printf("res_x = %d\nres_y = %d\nnorth_texture - %s\nsouth_texture - %s\neast_texture - %s\nwest_texture - %s\nsprite_texture - %s\nfloor_color = %s\nceiling_color= %s\n", 
	pars->res_x, pars->res_y, pars->north_texture, pars->south_texture, pars->east_texture, pars->west_texture, pars->sprite_texture, pars->floor_color, pars->ceiling_color);
	// if (check_validity(pars) != 1)
	// {
	// 	printf("I'm here\n");
	// 	return (1);
	// }
	while (text[i] == '\n' || text[i] == ' ')
		i++;
	if (text[i] != '1')
	{
		ft_putendl_fd("Error\nNo map in file", 1);
		return (1);
	}
	//printf("%s\n", &(text[i]));
	pars->map = ft_split(&(text[i]), '\n');
	print_map(pars->map);
	if (pars->map == NULL)
		flag = 1;
	return (flag);
}
