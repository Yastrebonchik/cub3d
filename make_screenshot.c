/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:48:38 by kcedra            #+#    #+#             */
/*   Updated: 2020/10/01 18:31:16 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void 		set_size(unsigned char **str, unsigned int size, int i, int len)
{
	int	begin;

	begin = i - len + 1;
	while (i >= begin)
	{
		(*str)[begin] = size % 256;
		size = size >> 8;
		begin++;
	}
}

static unsigned char *bmp_fileheader(t_vars *vars)
{
	unsigned char	*array;
	int 			size;

	array = (unsigned char*)malloc(sizeof(unsigned char) * 14);
	array[0] = 66;
	array[1] = 77;
	size = vars->pars->res_x * vars->pars->res_y * 3 + 54;
	set_size(&array, size, 5, 4);
	ft_memset(&(array[6]), 0, 4);
	size = 54;
	set_size(&array, size, 13, 4);
	vars->screenshot_flag = 1;
	return (array);
}

static unsigned char *bmp_infoheader(t_vars *vars)
{
	unsigned char 	*array;
	int				size;

	size = 40;
	array = (unsigned char*)malloc(sizeof(unsigned char) * size);
	set_size(&array, size, 3, 4);
	set_size(&array, vars->pars->res_x, 7, 4);
	set_size(&array, vars->pars->res_y, 11, 4);
	array[12] = 1;
	array[13] = 0;
	size = 24;
	set_size(&array, size, 15, 2);
	ft_memset(&(array[16]), 0, 24);
	return (array);
}

static unsigned char *bmp_pixeldata(t_vars *vars, int color)
{
	unsigned char	*array;
	int				i;
	int 			j;
	int 			k;
	int 			size;

	i = vars->pars->res_y - 1;
	k = 0;
	size = vars->pars->res_y * vars->pars->res_x * 3;
	array = (unsigned char*)malloc(sizeof(unsigned char) * (size));
	while (i >= 0)
	{
		j = -1;
		while (++j < vars->pars->res_x)
		{
			color = my_mlx_get_color(vars->data, j, i);
			set_size(&array, color, k + 2, 3);
			k += 3;
		}
		i--;
	}
	return (array);
}

void 		create_screenshot(t_vars *vars, char *argv)
{
	unsigned char	*file_header;
	unsigned char	*info_header;
	unsigned char	*pixel_data;
	int				fd;

	if (argv[6] != '\0' || ft_strncmp(argv, "--save", 6) != 0)
	{
		ft_putendl_fd("Error\nWrong argument", 1);
		exit(1);
	}
	while (vars->pars->res_x % 4 > 0)
		vars->pars->res_x--;
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	file_header = bmp_fileheader(vars);
	info_header = bmp_infoheader(vars);
	put_image(vars);
	pixel_data = bmp_pixeldata(vars, 0);
	write(fd, file_header, 14);
	write(fd, info_header, 40);
	write(fd, pixel_data, vars->pars->res_y * vars->pars->res_x * 3);
	free(file_header);
	free(info_header);
	free(pixel_data);
	close(fd);
	exit(0);
}