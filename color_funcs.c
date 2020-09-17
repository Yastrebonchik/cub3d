/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:38:29 by alexander         #+#    #+#             */
/*   Updated: 2020/09/16 16:39:20 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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