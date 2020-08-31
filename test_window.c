/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:33 by kcedra            #+#    #+#             */
/*   Updated: 2020/08/27 18:23:41 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             close_win(int keycode, t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    return (0);
}

int main(int argc, char **argv)
{
    t_vars  vars;
    t_data  img;
    t_pars  pars;
	int		color;
    int     i;
    int     j;
    int     k;

    if (argc != 2 && argc != 3)
    {
        ft_putendl_fd("Error\nWrong number of arguments", 1);
        return (0);
    }
    pars = parser(argv[1]);
    if (pars.flag == 1)
        return (0);
  	printf("Params flag = %d\n", pars.flag);
    ft_putendl_fd(pars.ceiling_color, 1);
    i = 800;
    k = 600;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, pars.res_x, pars.res_y, "cub3D");
    img.img = mlx_new_image(vars.mlx, pars.res_x, pars.res_y);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    &img.endian);
	color = atoi_color_base_16(pars.ceiling_color);
    printf("Atoi result = %d\n", color);
	//printf("Red color in mlx config %d\n", 0x0000FFFF);
	while (i < 1000)
    {
        j = 400;
        while (j < k)
        {
            my_mlx_pixel_put(&img, i, j, color);
            j++;
        }
        //k--;
        i++;
    }
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    mlx_key_hook(vars.win, close_win, &vars);
    mlx_loop(vars.mlx);
    return (0);
}