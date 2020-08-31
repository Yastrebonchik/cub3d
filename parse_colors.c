/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 15:29:06 by kcedra            #+#    #+#             */
/*   Updated: 2020/08/27 18:23:20 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	insert_color(char **color, char *r, char *g, char *b)
{
	if ((ft_strlen(r)) == 1)
	{
		(*color)[0] = '0';
		ft_strlcpy(&((*color)[1]), r, (ft_strlen(r)) + 1);
	}
	else
		ft_strlcpy(&((*color)[0]), r, (ft_strlen(r)) + 2);
	if ((ft_strlen(g)) == 1)
	{
		(*color)[2] = '0';
		ft_strlcpy(&((*color)[3]), g, (ft_strlen(g)) + 1);
	}
	else
		ft_strlcpy(&((*color)[2]), g, (ft_strlen(g)) + 2);
	if ((ft_strlen(b)) == 1)
	{
		(*color)[4] = '0';
		ft_strlcpy(&((*color)[5]), b, (ft_strlen(b)) + 1);
	}
	else
		ft_strlcpy(&((*color)[4]), b, (ft_strlen(b)) + 2);
	(*color)[6] = '\0';
}

static char	*unite_colors(int a, int y, int c)
{
	char	*color;
	char	*r;
	char	*g;
	char	*b;
	int		i;

	color = ft_calloc(7, sizeof(char));
	i = 0;
	r = ft_itoabase(a, 'X');
	g = ft_itoabase(y, 'X');
	b = ft_itoabase(c, 'X');
	//printf("%s %s %s\n", r, g, b);
	insert_color(&color, r, g, b);
	free(r);
	free(g);
	free(b);
	return (color);
}

int			itoa_color_base_16(char *text, int i, t_pars *pars, char type)
{
	int		a;
	int		b;
	int		c;
	int		flag;

	a = ft_atoi(&(text[i]));
	while (ft_isdigit(text[i]) == 1)
		i++;
	flag = (text[i++] != ',') ? 1 : 0;
	b = ft_atoi(&(text[i]));
	while (ft_isdigit(text[i]) == 1)
		i++;
	flag = (text[i++] != ',') ? 1 : flag;
	c = ft_atoi(&(text[i]));
	flag = (a > 255 || b > 255 || c > 255) ? 1 : flag;
	flag = (ft_isdigit(text[i]) == 1) ? flag : 1;
	while (ft_isdigit(text[i]) == 1)
		i++;
	if (type == 'F' && pars->floor_color == NULL)
		pars->floor_color = unite_colors(a, b, c);
	else if (type == 'C' && pars->ceiling_color == NULL)
		pars->ceiling_color = unite_colors(a, b, c);
	else
		flag = 1;
	return ((flag == 1) ? -1 : i);
}
