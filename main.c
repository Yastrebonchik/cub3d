/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:33 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/05 14:00:40 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	hooks_manage(int keycode, t_vars *vars)
{
	//printf("Key_code = %d\n", keycode);
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
		rotate_left(vars);
	if (keycode == 124)
		rotate_right(vars);
	return (0);
}

int			main(int argc, char **argv)
{
    t_vars  	vars;
    t_data  	img;
    t_pars  	pars;
    t_player 	player;
    t_map		map;
	t_data	cur_image;
	//int		color;

	if (argc != 2 && argc != 3)
    {
        ft_putendl_fd("Error\nWrong number of arguments", 1);
        return (0);
    }
    pars = parser(argv[1]);
    if (pars.flag == 1)
        return (0);
  	printf("Params flag = %d\n", pars.flag);
    //printf("Res_x = %d\nRes_y = %d\nNorth_texture - %s\nSouth_texture - %s\nEast_texture - %s\nWest_texture - %s\nSprite_texture - %s\nFloor_color = %s\nCeiling_color= %s\n",
	//pars.res_x, pars.res_y, pars.north_texture, pars.south_texture, pars.east_texture, pars.west_texture, pars.sprite_texture, pars.floor_color, pars.ceiling_color);
    //print_map(pars.map);
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
    player.pov = 0;
    player.x_pos = 480;
    player.y_pos = 236;
    vars.player = &player;
    vars.data = &img;
    vars.pars = &pars;
	vars.map = &map;
	cur_image.img = mlx_xpm_file_to_image(vars.mlx,
	vars.pars->north_texture, &(cur_image.width), &(cur_image.height));
    //put_image(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, cur_image.img, 0, 0);
    mlx_hook(vars.win, 2, 1L<<0, hooks_manage, &vars);
    mlx_loop(vars.mlx);
    return (0);
}