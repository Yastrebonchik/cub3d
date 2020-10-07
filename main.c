/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:33 by kcedra            #+#    #+#             */
/*   Updated: 2020/10/04 17:14:20 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Нужно отнормировать main.c raycasterы utils.c
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

static int 	destroy_window(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

static void	dst_array_allocate(t_vars *vars, t_pars *pars)
{
	double		*array;

	array = (double*)malloc(sizeof(double) * (pars->res_x + 1));
	vars->dst = array;
}

int			main(int argc, char **argv)
{
    t_vars  	vars;
    t_data  	img;
    t_pars  	pars;
    t_player 	player;
    t_map		map;

	if (argc != 2 && argc != 3)
    {
        ft_putendl_fd("Error\nWrong number of arguments", 1);
        return (0);
    }
	vars.mlx = mlx_init();
    pars = parser(argv[1], &vars);
    if (pars.flag == 1)
        exit (1);
    map_validity_check(&pars, &player);
    vars.win = mlx_new_window(vars.mlx, pars.res_x, pars.res_y, "CUB3D");
    img.img = mlx_new_image(vars.mlx, pars.res_x, pars.res_y);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    &img.endian);
	//printf("%p\n", img.img);
    map.map = pars.map;
    limit_counter(&map);
	dst_array_allocate(&vars, &pars);
    vars.player = &player;
    vars.data = &img;
    vars.pars = &pars;
	vars.map = &map;
	sprite_list_init(&vars);
    put_textures(&vars);
	print_textures(&vars);
	if (argc == 3)
		create_screenshot(&vars, argv[2]);
	put_image(&vars);
    mlx_hook(vars.win, 2, 1L<<0, hooks_manage, &vars);
	mlx_hook(vars.win, 17, 1L<<5, destroy_window, &vars);
    mlx_loop(vars.mlx);
    return (0);
}