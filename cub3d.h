/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:25:26 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/05 13:54:39 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define rotation_angle M_PI / 30
# define scale 64
# define speed 12
#include <fcntl.h>
#include <math.h>
#include "mlx/mlx.h"
#include "libft/libft.h"

#include "stdio.h"

typedef struct	s_pars
{
    int			flag;
    int			res_x;
    int			res_y;
    char		*north_texture;
    char		*south_texture;
    char		*west_texture;
    char		*east_texture;
    char		*sprite_texture;
    char		*floor_color;
    char		*ceiling_color;
    char		**map;
}				t_pars;

typedef struct	s_data {
    void		*img;
    char		*addr;
    int			bits_per_pixel;
    int			line_length;
    int			endian;
    int 		height;
    int 		width;
}				t_data;

typedef struct	s_map
{
	char		**map;
	int 		line_max;
	int 		column_max;
}				t_map;

typedef struct	s_player
{
	int			x_pos;
	int			y_pos;
	double 		pov;
}				t_player;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_player	*player;
	t_data		*data;
	t_data 		*cur_img;
	t_pars		*pars;
	t_map 		*map;
}				t_vars;

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
double  vertical_raycaster(int x_pos, double y_pos, double ray_angle, t_map *map);
double  horizontal_raycaster(double x_pos, int y_pos, double ray_angle, t_map *map);
double  min_of_2(double a, double b);
double	ft_abs(double a);
void    put_image(t_vars *vars);
void 	move_forward(t_vars *vars);
void 	move_backward(t_vars *vars);
void 	move_left(t_vars *vars);
void 	move_right(t_vars *vars);
void 	rotate_left(t_vars *vars);
void 	rotate_right(t_vars *vars);
void	text_join_n(char **text, char **line, int gnl);
void	pars_init(t_pars *pars);
void	limit_counter(t_map *map);
void 	position_detection(int x, int y, int *line, int *column);
void	draw_texture(t_vars *vars, int i, int *j, int height_of_wall);
void	print_map(char **map);
void	draw_map(t_vars *vars, t_data *img, char **map);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif