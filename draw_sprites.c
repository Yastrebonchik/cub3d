/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:00:02 by alexander         #+#    #+#             */
/*   Updated: 2020/09/25 22:49:28 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	reassign_elem(t_sprite **cur_elem)
{
	t_sprite	sub;

	sub.x = (*cur_elem)->x;
	sub.y = (*cur_elem)->y;
	sub.distance = (*cur_elem)->distance;
	(*cur_elem)->x = ((*cur_elem)->next)->x;
	(*cur_elem)->y = ((*cur_elem)->next)->y;
	(*cur_elem)->distance = ((*cur_elem)->next)->distance;
	((*cur_elem)->next)->x = sub.x;
	((*cur_elem)->next)->y = sub.y;
	((*cur_elem)->next)->distance = sub.distance;
}

static void	sort_sprites(t_vars *vars, t_sprite **begin_list)
{
	int			lst_len;
	t_sprite	*cur_elem;

	cur_elem = vars->lst_head;
	lst_len = 0;
	while (cur_elem != NULL)
	{
		cur_elem->distance = sqrt(pow(vars->player->x_pos -
		cur_elem->x, 2) + pow(vars->player->y_pos - cur_elem->y, 2));
		cur_elem = cur_elem->next;
		lst_len++;
	}
	while (lst_len != 0)
	{
		cur_elem = vars->lst_head;
		while (cur_elem != NULL)
		{
			if (cur_elem->next != NULL && cur_elem->distance <
			(cur_elem->next)->distance)
				reassign_elem(&cur_elem);
			cur_elem = cur_elem->next;
		}
		lst_len--;
	}
	(*begin_list) = vars->lst_head;
}

static void	draw_sprite(t_vars *vars, int sprite_size, int i, int j)
{
	int				height;
	int				coord;
	int				j_begin;
	int				i_begin;
	unsigned int	color;

	i_begin = i;
	j_begin = j;
	i = (i < 0) ? -1 : i;
	while ((++i - i_begin) < sprite_size && i < vars->pars->res_x)
	{
		if (vars->dst[i] > vars->dst[vars->pars->res_x])
		{
			j = j_begin;
			j = (j < 0) ? -1 : j;
			while ((++j - j_begin) < sprite_size && j < vars->pars->res_y)
			{
				coord = floor(vars->map->texture_scale * (i - i_begin));
				height = floor(vars->map->texture_scale * (j - j_begin));
				color = my_mlx_get_color(vars->sprite_texture, coord, height);
				if (color != 0)
					my_mlx_pixel_put(vars->data, i, j, color);
			}
		}
	}
}

void		check_sprites(t_vars *vars)
{
	t_sprite	*cur_elem;
	double		spr_abs_angle;
	double		sprite_size;
	int			h_offset;
	int			w_offset;

	sort_sprites(vars, &cur_elem);
	while (cur_elem != NULL)
	{
		spr_abs_angle = atan2(cur_elem->y - vars->player->y_pos, cur_elem->x
		- vars->player->x_pos);
		while (spr_abs_angle - vars->player->pov > M_PI)
			spr_abs_angle -= 2 * M_PI;
		while (spr_abs_angle - vars->player->pov < -M_PI)
			spr_abs_angle += 2 * M_PI;
		sprite_size = sprite_scale * ((double)vars->pars->res_x /
		(double)vars->pars->res_y) * vars->pars->res_y / cur_elem->distance;
		vars->dst[vars->pars->res_x] = cur_elem->distance;
		vars->map->texture_scale = 64 / (double)sprite_size;
		h_offset = (spr_abs_angle - vars->player->pov) * (vars->pars->res_x) /
		(M_PI / 3) + (vars->pars->res_x) / 2 - sprite_size / 2;
		w_offset = vars->pars->res_y / 2 - sprite_size / 2;
		draw_sprite(vars, (int)sprite_size, h_offset, w_offset);
		cur_elem = cur_elem->next;
	}
}
