/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:25:26 by kcedra            #+#    #+#             */
/*   Updated: 2020/09/25 22:38:53 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define rotation_angle M_PI / 60
# define scale 64
# define sprite_scale 60
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
	char 		player_sight_side;
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

typedef struct	s_sprite
{
	int 	x;
	int 	y;
	double 	distance;
	struct	s_sprite *next;
}				t_sprite;

typedef struct	s_map
{
	char		**map;
	int 		line_max;
	int 		column_max;
	int 		coord_x;
	int			coord_y;
	double 		texture_scale;
}				t_map;

typedef struct	s_player
{
	int			x_pos;
	int			y_pos;
	double 		pov;
}				t_player;

typedef struct	s_lin_col
{
	int		line;
	int		column;
	double	distance;
}				t_lin_col;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
    char        flag;
    char 		screenshot_flag;
	double		*dst;
	t_data		*data;
	t_data 		*north_texture;
    t_data      *south_texture;
    t_data      *east_texture;
    t_data      *west_texture;
    t_data 		*sprite_texture;
	t_sprite	*lst_head;
	t_player	*player;
	t_pars		*pars;
	t_map 		*map;
}				t_vars;

int		west_texture(char  *text, t_pars *pars, int i);
int		east_texture(char  *text, t_pars *pars, int i);
int		north_texture(char  *text, t_pars *pars, int i);
int		south_texture(char  *text, t_pars *pars, int i);
int		sprite_texture(char *text, t_pars *pars, int i);
int		line_counter(double *y_pos, double y_cur_pos, double ray_angle, int result);
int		color_error_management(char *text, t_pars *pars, int i);
int		resolution_error_managemnt(char *text, t_pars *pars, t_vars *vars);
int		args_error_management(char *text, t_pars *pars, int flag, t_vars *vars);
int		file_error_management(int gnl, char *filename);
int		check_validity(t_pars *pars);
int		atoi_color_base_16(char *color);
int		itoa_color_base_16(char *text, int i, t_pars *pars, char type);
int 	my_mlx_get_color(t_data *data, int x, int y);
int 	get_resolution(char *text, char res, t_vars *vars);
char	*ft_itoabase(long long int nb, char type);
t_pars	parser(char *filename, t_vars *vars);
double  vertical_raycaster(int x_pos, double y_pos, double ray_angle, t_map *map);
double  horizontal_raycaster(double x_pos, int y_pos, double ray_angle, t_map *map);
double  min_of_2_cub(double a, double b, t_vars *vars);
double 	left_half_end(t_lin_col *lin_col, t_map	*map, double *y_cur_pos, double ray_angle);
double	right_half_end(t_lin_col *lin_col, t_map *map, double *y_cur_pos, double ray_angle);
void	put_image(t_vars *vars);
void	move_forward(t_vars *vars);
void	move_backward(t_vars *vars);
void	move_left(t_vars *vars);
void	move_right(t_vars *vars);
void	rotation(t_vars *vars, int keycode);
void	text_join_n(char **text, char **line, int gnl);
void	pars_init(t_pars *pars);
void	limit_counter(t_map *map);
void	put_textures(t_vars *vars);
void	position_detection(int x, int y, int *line, int *column);
void	draw_texture(t_vars *vars, int i, int *j, int height_of_wall);
void	print_map(char **map);
void	check_side_of_world(t_vars *vars, double current_ray);
void	left_half_beg(t_lin_col *lin_col, int x_cur_pos, double *y_cur_pos, double ray_angle);
void	right_half_beg(t_lin_col *lin_col, int x_cur_pos, double *y_cur_pos, double ray_angle);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	map_validity_check(t_pars *pars, t_player *player);
void	sprite_list_init(t_vars *vars);
void	empty_line_check(char *text, int flag, int i);
void	walls_surrounding(char **map, char side);
void 	create_screenshot(t_vars *vars, char *argv);
void	check_sprites(t_vars *vars);

#endif