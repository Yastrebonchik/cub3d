/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_list_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 05:22:41 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/23 20:11:50 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_node(t_vars *vars, int line, int column)
{
	t_sprite	*new_elem;
	t_sprite	*cur_elem;
	
	if (vars->lst_head == NULL)
	{
		new_elem = (t_sprite*)malloc(sizeof(t_sprite));
		new_elem->next = NULL;
		new_elem->x = column * 64 + 32;
		new_elem->y = line * 64 + 32;
		vars->lst_head = new_elem;
	}
	else
	{
		cur_elem = vars->lst_head;
		while (cur_elem->next != NULL)
			cur_elem = cur_elem->next;
		new_elem = (t_sprite*)malloc(sizeof(t_sprite));
		new_elem->next = NULL;
		new_elem->x = column * 64 + 32;
		new_elem->y = line * 64 + 32;
		cur_elem->next = new_elem;
	}
}

void		sprite_list_init(t_vars *vars)
{
	int			line;
	int			column;

	line = 0;
	while (vars->map->map[line] != NULL)
	{
		column = 0;
		while (vars->map->map[line][column] != '\0')
		{
			if (vars->map->map[line][column] == '2')
				create_node(vars, line, column);
			column++;
		}
		line++;
	}
}