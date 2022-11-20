/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:14:46 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/14 16:28:51 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef __linux__

void	init_window(t_env *env)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	env->mlx = mlx;
	window = mlx_new_window(mlx, WIN_X_SZ, WIN_Y_SZ, "Cub3D");
	env->win = window;
	mlx_mouse_hide(mlx, window);
}

int	mouse_move_hook(int x, int y, t_env *env)
{
	int	dx;

	(void)y;
	dx = WIN_X_SZ / 2 - x;
	if (dx)
		env->playerDir = dvec_rot(env->playerDir,
				(double)(-M_PI * dx / 1800.0), 1);
	mlx_mouse_move(env->mlx, env->win, WIN_X_SZ / 2, WIN_Y_SZ / 2);
	return (1);
}

#elif __APPLE__

void	init_window(t_env *env)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	env->mlx = mlx;
	window = mlx_new_window(mlx, WIN_X_SZ, WIN_Y_SZ, "Cub3D");
	env->win = window;
	mlx_mouse_hide();
}

int	mouse_move_hook(int x, int y, t_env *env)
{
	int	dx;

	(void)y;
	dx = WIN_X_SZ / 2 - x;
	if (dx)
		env->playerDir = dvec_rot(env->playerDir,
				(double)(-M_PI * dx / 1800.0), 1);
	mlx_mouse_move(env->win, WIN_X_SZ / 2, WIN_Y_SZ / 2);
	return (1);
}
#endif

int	init_game(t_env *env)
{
	int	y;

	y = 0;
	while (y < 5)
	{
		env->tex[y].img = mlx_xpm_file_to_image(env->mlx,
				env->tex[y].file, &env->tex[y].width, &env->tex[y].height);
		if (env->tex[y].img == NULL)
			return (printf("Error:\nCan't open a texture\n"), EXIT_FAILURE);
		env->tex[y].buffer = (int *)mlx_get_data_addr(env->tex[y].img, \
				&env->tex[y].pixel_bits,
				&env->tex[y].line_bytes,
				&env->tex[y].endian);
		env->tex[y].line_bytes /= 4;
		y++;
	}
	env->img = mlx_new_image(env->mlx, WIN_X_SZ, WIN_Y_SZ);
	env->buffer = (int *)mlx_get_data_addr(env->img, \
		&env->pixel_bits, &env->line_bytes, &env->endian);
	env->line_bytes /= 4;
	mlx_hook(env->win, 2, 1L << 0, key_press_hook, env);
	mlx_hook(env->win, 3, 1L << 1, key_release_hook, env);
	mlx_hook(env->win, 6, 0L, mouse_move_hook, env);
	mlx_hook(env->win, 17, 0L, exit_game, env);
	return (EXIT_SUCCESS);
}
