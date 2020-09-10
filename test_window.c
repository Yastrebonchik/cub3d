/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:33 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/05 14:00:40 by kcedra           ###   ########.fr       */
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
	printf("Key_code = %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == 2)
	{
		vars->player->y_pos += 12;
		put_image(vars);
	}
	if (keycode == 1)
	{
		vars->player->x_pos -= 12;
		put_image(vars);
	}
	if (keycode == 13)
	{
		vars->player->x_pos += 12;
		put_image(vars);
	}
	if (keycode == 0)
	{
		vars->player->y_pos -= 12;
		put_image(vars);
	}
	if (keycode == 123)
	{
		vars->player->pov -= rotation_angle;
		put_image(vars);
	}
	if (keycode == 124)
	{
		vars->player->pov += rotation_angle;
		put_image(vars);
	}
	return (0);
}

int main(int argc, char **argv)
{
    t_vars  	vars;
    t_data  	img;
    t_pars  	pars;
    t_player 	player;
    t_map		map;
    //double  pov;
	//int		color;
    //int     i;
    //int     j;
    //int     k;

    if (argc != 2 && argc != 3)
    {
        ft_putendl_fd("Error\nWrong number of arguments", 1);
        return (0);
    }
    pars = parser(argv[1]);
    //if (pars.flag == 1)
    //    return (0);
  	//printf("Params flag = %d\n", pars.flag);
    //ft_putendl_fd(pars.ceiling_color, 1);
    //printf("Res_x = %d\nRes_y = %d\nNorth_texture - %s\nSouth_texture - %s\nEast_texture - %s\nWest_texture - %s\nSprite_texture - %s\nFloor_color = %s\nCeiling_color= %s\n",
	//pars.res_x, pars.res_y, pars.north_texture, pars.south_texture, pars.east_texture, pars.west_texture, pars.sprite_texture, pars.floor_color, pars.ceiling_color);
    //print_map(pars.map);
    //i = 800;
    //k = 600;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, pars.res_x, pars.res_y, "CUB3D");
    img.img = mlx_new_image(vars.mlx, pars.res_x, pars.res_y);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    &img.endian);
    map.map = pars.map;
	//color = atoi_color_base_16(pars.ceiling_color);
    //printf("Atoi result = %d\n", color);
    //draw_map(&vars, &img, pars.map);
    limit_counter(&map);
    player.pov = 6.414085;
    player.x_pos = 480;
    player.y_pos = 236;
    vars.player = &player;
    vars.data = &img;
    vars.pars = &pars;
	vars.map = &map;
    put_image(&vars);
    //distance = horizontal_raycaster(129, -65,5 * M_PI_4, pars.map, 7, 2);
    //printf("Distance = %f\n", distance);
    //distance = vertical_raycaster(128, -64, M_PI, pars.map, 7, 2);
    //printf("Distance = %f\n", distance);
    //mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    mlx_hook(vars.win, 2, 1L<<0, close_win, &vars);
    mlx_loop(vars.mlx);
    return (0);
}