/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:00:02 by alexander         #+#    #+#             */
/*   Updated: 2020/09/21 14:29:35 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	draw_sprite(t_vars *vars, int height, int i, int j, int j_begin)
{
//	int 	cur_height;
//	int 	coord;
//	int 	color;
//	double 	d_cur_height;

	//coord = vars->map->texture_scale
//	d_cur_height = vars->map->texture_scale * (double)(*j -
//	((vars->pars->res_y - height) / 2));
//	cur_height = floor(d_cur_height);
//	if (vars->flag == 'W')
//		color = my_mlx_get_color(vars->west_texture, coord, cur_height);
//	else if (vars->flag == 'S')
//		color = my_mlx_get_color(vars->south_texture, coord, cur_height);
//	else if (vars->flag == 'N')
//		color = my_mlx_get_color(vars->north_texture, coord, cur_height);
//	else
//		color = my_mlx_get_color(vars->east_texture, coord, cur_height);
	height = 3;
	while ((j - j_begin) < 64)
	{
		//printf("Kek\n");
		my_mlx_pixel_put(vars->data, i, (j)++, 0x00000000);
	}
}

void	check_sprites(t_vars *vars)
{
	t_sprite 	*cur_elem;
	double		spr_abs_angle;
	double 		spr_plr_angle;
	double 		distance;
	double 		height;
	//int 		begin_h;
	//int 		begin_w;
	//double 		width;
//	int 		h_offset;
//	int 		w_offset;

	cur_elem = vars->lst_head;
	while (cur_elem != NULL)
	{
		//printf("Player x = %d and player y = %d\n", vars->player->x_pos, vars->player->y_pos);
		//printf("Sprite x = %d and sprite y = %d\n", cur_elem->x, cur_elem->y);
		spr_abs_angle = atan2(cur_elem->y - vars->player->y_pos, cur_elem->x - vars->player->x_pos);
		spr_plr_angle = spr_abs_angle - vars->player->pov;
		while (spr_plr_angle > M_PI)
			spr_plr_angle -= 2 * M_PI;
		while (spr_plr_angle < -M_PI)
			spr_plr_angle += 2 * M_PI;
		if (ft_abs(spr_plr_angle) < M_PI / 6)
		{
			//i = 0;
			distance = sqrt(pow(vars->player->x_pos - cur_elem->x, 2) + pow(vars->player->y_pos - cur_elem->y, 2));
			printf("Sprite angle = %f\n", spr_plr_angle);
			height = min_of_2(vars->pars->res_y / 2, vars->pars->res_y / distance);
			printf("Distance = %f\n", vars->pars->res_y / distance);
//			width = min_of_2(vars->pars->res_x / 2, 64 / distance * (vars->pars->res_y / (2 * tan(M_PI / 6))));
//			h_offset = ft_abs(spr_plr_angle) * (vars->pars->res_x) / (M_PI / 3) + (vars->pars->res_x)/ - height;
//			w_offset = vars->pars->res_y - height;
//			vars->map->texture_scale = 64/height;
//			begin_h = h_offset;
//			begin_w = w_offset;
//			printf("Scale = %f\n", vars->map->texture_scale);
//			//printf ("w_offset - begin_w = %d\n", w_offset - begin_w);
//			while ((w_offset - begin_w)  < 64)
//			{
//				draw_sprite(vars, height, w_offset, h_offset, begin_h);
//				w_offset++;
//			}
			//printf("Sprite line = %d and sprite column = %d\n", cur_elem->y / 64, cur_elem->x / 64);
		}
		cur_elem = cur_elem->next;
	}
}