/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:24:12 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/24 16:43:16 by narnaud          ###   ########.fr       */
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

typedef struct s_map
{
	size_t	wide;
	size_t	deep;
	char	**map;
}	t_map;

typedef struct s_env
{
	int		step;
	char	*wallTexture[4];
	int		floorColor;
	int		ceilColor;
	t_slist	*raw_map;
	int		deep;
	t_map	*map;
	void	*mlx;
	void	*window;
}	t_env;

t_env	*parse_envFile(char *filename);
char	*get_next_line(int fd);

#endif
