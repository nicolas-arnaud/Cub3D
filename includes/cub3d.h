/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:24:12 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/30 18:02:08 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# define WIN_X_SZ	900
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

typedef struct s_env
{
	int	wide;
	int	deep;
	char	*wallTexture[4];
	int		floorColor;
	int		ceilColor;
	char	**map;
	void	*mlx;
	void	*win;
	void	*img;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	int		*buffer;
	t_vec	playerPos;
	int		yaw;
}	t_env;

int		rgb_to_int(char	**rgb);
t_env	*parse_envFile(char *filename);
char	*get_next_line(int fd);

#endif
