/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:24:12 by narnaud           #+#    #+#             */
/*   Updated: 2022/06/01 18:13:08 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# define WIN_X_SZ	1760
# define WIN_Y_SZ	900

# define BUFFER_SIZE 4096
# define UNIT 200
# define WALL_HEIGHT 200
# define PLAYER_HEIGHT 170
# define SCREEN_DISTANCE 50

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "../includes/libft.h"
# ifdef __linux__
#  include "../includes/mlx.h"
# elif __APPLE__
#  include <mlx.h>
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
}	t_vec_d;

typedef struct s_rectangle
{
	int startX;
	int startY;
	int	sizeX;
	int sizeY;
	int color;
}	t_rectangle;

typedef struct s_control
{
	int	up;
	int	down;
	int	left;
	int	right;
}	t_control;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	void	*img;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	int		*buffer;
	int		minimap;
	int		controls[KEYS_LIMIT];
	char	*wallTexture[4];
	int		floorColor;
	int		ceilColor;
	char	**map;
	int		wide;
	int		deep;
	t_vec_d	playerPos;
	t_vec_d	playerDir;
	t_vec_d	camPlan;
}	t_env;

void	render_minimap(t_env *env, t_vec size);
void	render_view(t_env *env);
void	render(t_env *env);

int		key_press_hook(int keycode, t_env *env);
int		key_release_hook(int keycode, t_env *env);
int		update_hook(t_env *env);

int		rgb_to_int(char	**rgb);
void	set_vec(t_vec_d *vec, double x, double y);
double	vec_len(t_vec_d vec);
t_vec_d	rot_vec(t_vec_d vec, double rad, double init_len);

t_env	*parse_envFile(char *filename);
char	*get_next_line(int fd);

#endif
