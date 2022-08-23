/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/08/23 16:40:30 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
/* ToDo:
 * Handle bad inits
 */
void	init_window(t_env *env)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	env->mlx = mlx;
	window = mlx_new_window(mlx, WIN_X_SZ, WIN_Y_SZ, "FdF");
	env->win = window;
	mlx_mouse_hide();
}

void	init_game(t_env *env)
{
	int	y;

	y = 0;
	while (y < 5)
	{
		env->tex[y].img = mlx_xpm_file_to_image(env->mlx,
				env->tex[y].file, &env->tex[y].width, &env->tex[y].height);
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
}

void	debug(t_env *env)
{
	int	y;

	if (!DEBUG)
		return ;
	y = 0;
	printf("\e[1;32m========> WALLS <========\e[0m\nNorth: %s\nSouth: %s\nWest: %s\nEast: %s\n",\
			env->tex[0].file, env->tex[1].file,\
			env->tex[2].file, env->tex[3].file);
	printf("\e[1;32m========================\e[0m\n");
	printf("=> Floor color: %d\n=> Ceil color: %d\n", env->floorColor, env->ceilColor);
	printf("\e[1;32m========> MAP <========\e[0m\n");
	while (env->map[y])
		printf("%s\n", env->map[y++]);
}

int	main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		return (EXIT_FAILURE);
	env = parse_file(argv[1]);
	if (!env)
		return (EXIT_FAILURE);
	debug(env);
	init_window(env);
	init_game(env);
	render(env);
	mlx_loop_hook(env->mlx, update_hook, env);
	mlx_loop(env->mlx);
	mlx_destroy_image(env->mlx, env->img);
	return (EXIT_SUCCESS);
}
