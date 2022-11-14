/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:24:12 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/14 10:35:59 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_X_SZ	1760
# define WIN_Y_SZ	900
# define BUFFER_SIZE 4096

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "libft.h"
# ifdef __linux__
#  include "mlx.h"
# elif __APPLE__
#  include "mlxmac.h"
# endif
# include "mlx_keycode.h"

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vec;

typedef struct s_vector_d
{
	double	x;
	double	y;
}	t_dvec;

typedef struct s_rectangle
{
	t_vec	start;
	t_vec	size;
	int 	color;
}	t_rect;

typedef struct s_raycast
{
	t_dvec	vec;
	int		*cell;
	double	sDist[2];
	double	dDist[2];
	int		*step;	
	int		side;
	int		tex;
	double	dist;
	double	wallX;
	int		x;
}	t_rc;

typedef struct s_img
{
	char	*file;
	int		*img;
	int		width;
	int		height;
	int		*buffer;
	int		pixel_bits;
	int		line_bytes;
	int		endian;

}	t_img;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	void	*img;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	int		*buffer;
	t_img	tex[5];
	int		minimap;
	int		controls[KEYS_LIMIT];
	int		mouseX;
	int		floorColor;
	int		ceilColor;
	char	**map;
	int		wide;
	int		deep;
	t_dvec	playerPos;
	t_dvec	playerDir;
	t_dvec	camPlan;
}	t_env;

// Render
void	check_side(t_rc *rc);
void	init_ray(t_env *env, t_rc *rc);
int		ray_hit(t_env *env, t_rc *rc);
void	draw_rectangle(t_env *env, t_rect rect, int borders);
t_rect	get_mm_cell(char type, t_vec pos, t_vec delta);
void	render_minimap(t_env *env, t_vec size);
void	render_view(t_env *env);
void	render(t_env *env);

// MLX
int		key_press_hook(int keycode, t_env *env);
int		key_release_hook(int keycode, t_env *env);
int		mouse_down_hook(int buton, int x, int y, t_env *env);
int		mouse_move_hook(int x, int y, t_env *env);
int		mouse_up_hook(int buton, int x, int y, t_env *env);
int		update_hook(t_env *env);
void	init_window(t_env *nv);
void	init_game(t_env *env);

// Utils
void	vec_set(t_vec *vec, int x, int y);
t_vec	vec_mult(t_vec v1, t_vec v2);
void	dvec_set(t_dvec *vec, double x, double y);
double	dvec_len(t_dvec vec);
t_dvec	dvec_rot(t_dvec vec, double rad, double init_len);

// Parsing
int		rgb_to_int(char	**rgb);
char	**create_map_array(t_slist	*e_lst, int wide, int deep);
int		is_in_open_room(t_env *env, int x, int y);
int		find_player(t_env *env);
t_env	*load_map(char *filename);
char	*get_next_line(int fd);

#endif
