/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:46:00 by kcedra            #+#    #+#             */
/*   Updated: 2020/10/04 16:56:04 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_init(t_player *player, int line, int column, char view)
{
	if (view == 'E')
		player->pov = 0;
	else if (view == 'S')
		player->pov = M_PI_2;
	else if (view == 'W')
		player->pov = M_PI;
	else if (view == 'N')
		player->pov = 3 * M_PI_2;
	player->x_pos = column * 64 + 32;
	player->y_pos = line * 64 + 32;
}

static void	player_check(t_pars *pars, t_player *player, int flag)
{
	int	i;
	int j;

	i = 0;
	while (pars->map[i] != NULL)
	{
		j = 0;
		while (pars->map[i][j] != '\0')
		{
			if (pars->map[i][j] == 'N' || pars->map[i][j] == 'W'
			|| pars->map[i][j] == 'E' || pars->map[i][j] == 'S')
			{
				flag++;
				pars->player_sight_side = pars->map[i][j];
				player_init(player, i, j, pars->player_sight_side);
			}
			j++;
		}
		i++;
	}
	if (flag != 1)
	{
		ft_putendl_fd("Error\nWrong quantity of players", 1);
		exit(0);
	}
}

void		empty_line_check(char *text, int flag, int i)
{
	int	strlen;

	while (text[++i] != '\0')
	{
		strlen = 0;
		flag = 0;
		while (text[i] != '\n' && text[i] != '\0')
		{
			flag = (text[i] == ' ') ? flag + 1 : flag;
			strlen++;
			i++;
		}
		if (flag == strlen)
		{
			while (text[++i] != '\0')
			{
				if (text[i] != '\n' && text[i] != ' ')
				{
					ft_putendl_fd("Error\nWrong map", 1);
					exit(1);
				}
			}
		}
	}
}

static void	symbols_check(t_pars *pars)
{
	int		i;
	int		j;
	char	side;

	i = 0;
	side = pars->player_sight_side;
	while (pars->map[i] != NULL)
	{
		j = 0;
		while (pars->map[i][j] != '\0')
		{
			if (pars->map[i][j] != '0' && pars->map[i][j] != '1' &&
			pars->map[i][j] != '2' && pars->map[i][j] != side &&
			pars->map[i][j] != ' ')
			{
				ft_putendl_fd("Error\nWrong map", 1);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void		map_validity_check(t_pars *pars, t_player *player)
{
	int flag;

	flag = 0;
	player_check(pars, player, flag);
	symbols_check(pars);
	walls_surrounding(pars->map, pars->player_sight_side);
}
