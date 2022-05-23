/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:24:12 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/22 14:10:24 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define UNIT 100
# define WALL_HEIGHT 200
# define PLAYER_HEIGHT 170
# define SCREEN_DISTANCE 50

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sting.h>
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
	int	z;
}	t_vec;

char *get_next_line(int fd);

#endif
