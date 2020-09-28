/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:48:38 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/28 17:48:40 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void 		set_size(unsigned char **str, unsigned int size, int i, int len)
{
	int	begin;

	begin = i - len;
	while (i > begin)
	{
		(*str)[i] = size % 256;
		size = size >> 8;
		i--;
	}
}

static unsigned char *bmp_fileheader(t_vars *vars)
{
	unsigned char	*array;
	int 			size;

	array = (unsigned char*)malloc(sizeof(unsigned char) * 14);
	array[0] = 66;
	array[1] = 77;
	size = vars->pars->res_x * vars->pars->res_y * 4 +54;
	set_size(&array, size, 5, 4);
	array[6] = 0;
	array[7] = 0;
	array[8] = 0;
	array[9] = 0;
	size = 54;
	set_size(&array, size, 13, 4);
	return (array);
}

static unsigned char *bmp_infoheader(t_vars *vars)
{
	unsigned char 	*array;
	int				size;

	size = 40;
	array = (unsigned char*)malloc(sizeof(unsigned char) * 40);
	set_size(&array, size, 3, 4);
	//printf("%d\n%d\n%d\n%d\n", array[0], array[1], array[2], array[3]);
	set_size(&array, vars->pars->res_x, 7, 4);
	set_size(&array, vars->pars->res_y, 11, 4);
	//printf("%d\n%d\n%d\n%d\n", array[4], array[5], array[6], array[7]);
	array[12] = 0;
	array[13] = 1;
	size = 32;
	set_size(&array, size, 15, 2);
	ft_memset(&(array[16]), 0, 4);
	set_size(&array, vars->pars->res_x * vars->pars->res_y * 4, 23, 4);
	set_size(&array, 2835, 27, 4);
	set_size(&array, 2835, 31, 4);
	set_size(&array, 0, 35, 4);
	set_size(&array, 0, 39, 4);
	//printf("%d\n%d\n%d\n%d\n", array[8], array[9], array[10], array[11]);
	return (array);
}

static unsigned char *bmp_pixeldata(t_vars *vars, int color)
{
	unsigned char	*array;
	int				i;
	int 			j;
	int 			k;
	int 			size;

	i = 0;
	k = 0;
	size = vars->pars->res_y * vars->pars->res_x * 4;
	array = (unsigned char*)malloc(sizeof(unsigned char) * (size));
	while (i < vars->pars->res_x)
	{
		j = vars->pars->res_y;
		while (j > 0)
		{
			j--;
			color = my_mlx_get_color(vars->data, i, j);
			set_size(&array, color, k + 3, 4);
			k += 4;
		}
		i++;
	}
	return (array);
}

void 		create_screenshot(t_vars *vars, char *argv)
{
	unsigned char	*file_header;
	unsigned char	*info_header;
	unsigned char	*pixel_data;
	int 	fd;
	int 	size;
	int		i;

	i = -1;
	argv[1] = '\0';
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	vars->screenshot_flag = 1;
	put_image(vars);
	file_header = bmp_fileheader(vars);
	info_header = bmp_infoheader(vars);
	pixel_data = bmp_pixeldata(vars, 0);
	while (++i < 14)
		printf("%d\n", file_header[i]);
	i = -1;
	while (++i < 40)
		printf("%d\n", info_header[i]);
	write(fd, file_header, 14);
	write(fd, info_header, 40);
	size = vars->pars->res_y * vars->pars->res_x * 4;
	printf("==============\n%d\n%d\n%d\n%d\n", pixel_data[0], pixel_data[1], pixel_data[2], pixel_data[3]);
	write(fd, pixel_data, size);
	close(fd);
	free(file_header);
	free(info_header);
	free(pixel_data);
	exit(0);
}