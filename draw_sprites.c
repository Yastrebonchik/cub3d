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

void	check_sprites(t_vars *vars)
{
	t_sprite 	*cur_elem;
	double		spr_abs_angle;
	
	cur_elem = vars->lst_head;
	while (cur_elem != NULL)
	{
		//printf("Player x = %d and player y = %d\n", vars->player->x_pos, vars->player->y_pos);
		//printf("Sprite x = %d and sprite y = %d\n", cur_elem->x, cur_elem->y);
		spr_abs_angle = atan2(cur_elem->y - vars->player->y_pos, cur_elem->x - vars->player->x_pos);
		//printf("Sprite angle = %f\n", spr_abs_angle);
		//if (ft_abs(vars->player->pov - spr_abs_angle) < M_PI / 6)
		//printf("Sprite line = %d and sprite column = %d", cur_elem->x, cur_elem->y);
		cur_elem = cur_elem->next;
	}
}