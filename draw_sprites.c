/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:00:02 by alexander         #+#    #+#             */
/*   Updated: 2020/09/24 18:00:17 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	draw_sprite(t_vars *vars, int sprite_size, int i, int j)
{
	int 			height;
	int 			coord;
	int				j_begin; 
	int 			i_begin;
	unsigned int	color;
	
	i_begin = i;
	j_begin = j;
	while ((i - i_begin) < sprite_size)
	{
		if (vars->dst[i] > vars->dst[vars->pars->res_x])
		{
			j = j_begin;
			//vars->dst[i] = vars->dst[vars->pars->res_x];
			while ((j - j_begin) < sprite_size)
			{
				coord = floor(vars->map->texture_scale * (i - i_begin));
				height = floor(vars->map->texture_scale * (j - j_begin));
				color = my_mlx_get_color(vars->sprite_texture, coord, height);
				if (color != 0)
				{
					my_mlx_pixel_put(vars->data, i, j, color);
					vars->dst[i] = vars->dst[vars->pars->res_x];
				}
				j++;
			}
		}
		i++;
	}
}

void	check_sprites(t_vars *vars)
{
	t_sprite 	*cur_elem;
	double		spr_abs_angle;
	double 		spr_plr_angle;
	double 		distance;
	double 		sprite_size;
	int 		h_offset;
	int 		w_offset;

	cur_elem = vars->lst_head;
	while (cur_elem != NULL)
	{
		//printf("Player x = %d and player y = %d\n", vars->player->x_pos, vars->player->y_pos);
		//printf("Sprite column = %d and sprite line = %d\n", cur_elem->x / 64, cur_elem->y / 64);
		spr_abs_angle = atan2(cur_elem->y - vars->player->y_pos, cur_elem->x - vars->player->x_pos);
		//spr_plr_angle = spr_abs_angle - vars->player->pov;
		while (spr_abs_angle - vars->player->pov > M_PI)
			spr_abs_angle -= 2 * M_PI;
		while (spr_abs_angle - vars->player->pov < -M_PI)
			spr_abs_angle += 2 * M_PI;
		spr_plr_angle = spr_abs_angle - vars->player->pov;
		distance = sqrt(pow(vars->player->x_pos - cur_elem->x, 2) + pow(vars->player->y_pos - cur_elem->y, 2));
		sprite_size = sprite_scale * vars->pars->res_y / distance;
		if (ft_abs(spr_plr_angle) < M_PI / 6 + sqrt((distance * distance) + (sprite_size * sprite_size)))
		{
			//distance = sqrt(pow(vars->player->x_pos - cur_elem->x, 2) + pow(vars->player->y_pos - cur_elem->y, 2));
			vars->dst[vars->pars->res_x] = distance;
			printf("Distance = %f\n", distance);
			vars->map->texture_scale = 64 / (double)sprite_size;
			h_offset = spr_plr_angle * (vars->pars->res_x) / (M_PI / 3) + (vars->pars->res_x) / 2 - sprite_size / 2;
			w_offset = vars->pars->res_y / 2 - sprite_size / 2;
			//sprite_size = min_of_2(vars->pars->res_y / 2, sprite_scale * vars->pars->res_y / distance);
			draw_sprite(vars, (int)sprite_size, h_offset, w_offset);
		}
		cur_elem = cur_elem->next;
	}
}