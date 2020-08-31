/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:26:56 by kcedra            #+#    #+#             */
/*   Updated: 2020/08/27 14:21:49 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		west_texture(char *text, t_pars *pars, int i)
{
	int flag;
	int end;

	flag = 0;
	if (pars->west_texture != NULL)
		flag = 1;
	if (text[i] != 'W' || text[i + 1] != 'E' || text[i + 2] != ' ')
		flag = 1;
	i += 2;
	while (text[i] == ' ')
		i++;
	end = ft_strchrnum(&(text[i]), '\n');
	end = (ft_strchrnum(&(text[i]), ' ') > end) ? end :
	ft_strchrnum(&(text[i]), ' ');
	pars->west_texture = ft_substr(text, i, end);
	while (text[i] != ' ' && text[i] != '\n' && text[i] != '\0')
		i++;
	while (text[i] == ' ')
		i++;
	if (text[i] != '\n')
		flag = 1;
	if (flag == 1)
		ft_putendl_fd("Error\nInvalid west texture config", 1);
	return (flag);
}

int		east_texture(char *text, t_pars *pars, int i)
{
	int flag;
	int end;

	flag = 0;
	if (pars->east_texture != NULL)
		flag = 1;
	if (text[i] != 'E' || text[i + 1] != 'A' || text[i + 2] != ' ')
		flag = 1;
	i += 2;
	while (text[i] == ' ')
		i++;
	end = ft_strchrnum(&(text[i]), '\n');
	pars->east_texture = ft_substr(text, i, end);
	while (text[i] != ' ' && text[i] != '\n' && text[i] != '\0')
		i++;
	while (text[i] == ' ')
		i++;
	if (text[i] != '\n')
		flag = 1;
	if (flag == 1)
		ft_putendl_fd("Error\nInvalid east texture config", 1);
	return (flag);
}

int		north_texture(char *text, t_pars *pars, int i)
{
	int flag;
	int end;

	flag = 0;
	if (pars->north_texture != NULL)
		flag = 1;
	if (text[i] != 'N' || text[i + 1] != 'O' || text[i + 2] != ' ')
		flag = 1;
	i += 2;
	while (text[i] == ' ')
		i++;
	end = ft_strchrnum(&(text[i]), '\n');
	end = (ft_strchrnum(&(text[i]), ' ') > end) ? end :
	ft_strchrnum(&(text[i]), ' ');
	pars->north_texture = ft_substr(text, i, end);
	while (text[i] != ' ' && text[i] != '\n' && text[i] != '\0')
		i++;
	while (text[i] == ' ')
		i++;
	if (text[i] != '\n')
		flag = 1;
	if (flag == 1)
		ft_putendl_fd("Error\nInvalid north texture config", 1);
	return (flag);
}

int		south_texture(char *text, t_pars *pars, int i)
{
	int flag;
	int end;

	flag = 0;
	if (pars->south_texture != NULL)
		flag = 1;
	if (text[i] != 'S' || text[i + 1] != 'O' || text[i + 2] != ' ')
		flag = 1;
	i += 2;
	while (text[i] == ' ')
		i++;
	end = ft_strchrnum(&(text[i]), '\n');
	end = (ft_strchrnum(&(text[i]), ' ') > end) ? end :
	ft_strchrnum(&(text[i]), ' ');
	pars->south_texture = ft_substr(text, i, end);
	while (text[i] != ' ' && text[i] != '\n' && text[i] != '\0')
		i++;
	while (text[i] == ' ')
		i++;
	if (text[i] != '\n')
		flag = 1;
	if (flag == 1)
		ft_putendl_fd("Error\nInvalid south texture config", 1);
	return (flag);
}

int		sprite_texture(char *text, t_pars *pars, int i)
{
	int flag;
	int end;

	flag = 0;
	if (pars->sprite_texture != NULL)
		flag = 1;
	if (text[i] != 'S' || text[i + 1] != ' ')
		flag = 1;
	i += 1;
	while (text[i] == ' ')
		i++;
	end = ft_strchrnum(&(text[i]), '\n');
	end = (ft_strchrnum(&(text[i]), ' ') > end) ? end :
	ft_strchrnum(&(text[i]), ' ');
	pars->sprite_texture = ft_substr(text, i, end);
	while (text[i] != ' ' && text[i] != '\n' && text[i] != '\0')
		i++;
	while (text[i] == ' ')
		i++;
	if (text[i] != '\n')
		flag = 1;
	if (flag == 1)
		ft_putendl_fd("Error\nInvalid sprite texture config", 1);
	return (flag);
}
