/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:25:26 by kcedra            #+#    #+#             */
/*   Updated: 2020/08/27 19:36:12 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <fcntl.h>
#include <math.h>
#include "mlx/mlx.h"
#include "libft/libft.h"
#include "stdio.h"

typedef struct s_pars
{
    int     flag;
    int     res_x;
    int     res_y;
    char    *north_texture;
    char    *south_texture;
    char    *west_texture;
    char    *east_texture;
    char    *sprite_texture;
    char    *floor_color;
    char    *ceiling_color;
    char    **map;
}              t_pars;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

int		west_texture(char  *text, t_pars *pars, int i);
int		east_texture(char  *text, t_pars *pars, int i);
int		north_texture(char  *text, t_pars *pars, int i);
int		south_texture(char  *text, t_pars *pars, int i);
int		sprite_texture(char *text, t_pars *pars, int i);
int		color_error_management(char *text, t_pars *pars, int i);
int		resolution_error_managemnt(char *text, t_pars *pars);
int		args_error_management(char *text, t_pars *pars);
int		file_error_management(int gnl, char *filename);
int		check_validity(t_pars *pars);
int		atoi_color_base_16(char *color);
int		itoa_color_base_16(char *text, int i, t_pars *pars, char type);
char	*ft_itoabase(long long int nb, char type);
t_pars	parser(char *filename);
void	text_join_n(char **text, char **line, int gnl);
void	pars_init(t_pars *pars);
void	print_map(char **map);

#endif