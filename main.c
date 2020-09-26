/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:33 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/24 22:10:48 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Нужно отнормировать main.c put_image.c raycasterы utils.c
static int	hooks_manage(int keycode, t_vars *vars)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 1)
		move_backward(vars);
	if (keycode == 13)
		move_forward(vars);
	if (keycode == 0)
		move_left(vars);
	if (keycode == 2)
		move_right(vars);
	if (keycode == 123)
		rotation(vars, 123);
	if (keycode == 124)
		rotation(vars, 124);
	return (0);
}

// static int 	destroy_window(int keycode, t_vars *vars)
// {
// 	keycode = 3;
//     mlx_destroy_window(vars->mlx, vars->win);
// 	exit(0);
// }

int			main(int argc, char **argv)
{
    t_vars  	vars;
    t_data  	img;
    t_pars  	pars;
    t_player 	player;
    t_map		map;
	double		*array;

	if (argc != 2 && argc != 3)
    {
        ft_putendl_fd("Error\nWrong number of arguments", 1);
        return (0);
    }
	vars.mlx = mlx_init();
    pars = parser(argv[1], &vars);
    if (pars.flag == 1)
        exit (1);
  	//printf("Params flag = %d\n", pars.flag);
    //printf("Res_x = %d\nRes_y = %d\nNorth_texture - %s\nSouth_texture - %s\nEast_texture - %s\nWest_texture - %s\nSprite_texture - %s\nFloor_color = %s\nCeiling_color= %s\n",
	//pars.res_x, pars.res_y, pars.north_texture, pars.south_texture, pars.east_texture, pars.west_texture, pars.sprite_texture, pars.floor_color, pars.ceiling_color);
    //print_map(pars.map);
    map_validity_check(&pars, &player);
    vars.win = mlx_new_window(vars.mlx, pars.res_x, pars.res_y, "CUB3D");
    img.img = mlx_new_image(vars.mlx, pars.res_x, pars.res_y);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    &img.endian);
    map.map = pars.map;
    limit_counter(&map);
	array = (double*)malloc(sizeof(double) * (pars.res_x + 1));
	vars.dst = array;
    vars.player = &player;
    vars.data = &img;
    vars.pars = &pars;
	vars.map = &map;
	sprite_list_init(&vars);
    put_textures(&vars);
	print_textures(&vars);
	put_image(&vars);
    mlx_hook(vars.win, 2, 1L<<0, hooks_manage, &vars);
	//mlx_hook(vars.win, 17, 0, destroy_window, &vars);
    mlx_loop(vars.mlx);
    return (0);
}