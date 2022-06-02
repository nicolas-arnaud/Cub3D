/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/06/02 17:35:19 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_window(t_env *env)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	//if (!mlx)
		//exit(error_msg("Mlx fail to init", 1));
	env->mlx = mlx;
	window = mlx_new_window(mlx, WIN_X_SZ, WIN_Y_SZ, "FdF");
	//if (!window)
		//exit(error_msg("Mlx fail to create window", 1));
	env->win = window;
}

int	main(int argc, char **argv)
{
	t_env	*env;
	int		y;

	if (argc != 2)
		return (EXIT_FAILURE);
	env = parse_envFile(argv[1]);	
	if (!env)
		return (EXIT_FAILURE);
	if (DEBUG)
	{
		printf("\e[1;32m========> WALLS <========\e[0m\nNorth: %s\nSouth: %s\nWest: %s\nEast: %s\n",\
				env->wall[0].file, env->wall[1].file,\
				env->wall[2].file, env->wall[3].file);
		printf("\e[1;32m========================\e[0m\n");
		printf("=> Floor color: %d\n=> Ceil color: %d\n", env->floorColor, env->ceilColor);
		printf("\e[1;32m========> MAP <========\e[0m\n");
		y = 0;
		while (env->map[y])
			printf("%s\n", env->map[y++]);
	}
	init_window(env);
	y = 0;
	while (y < 4)
	{
		env->wall[y].img = mlx_xpm_file_to_image(env->mlx,
			env->wall[y].file, &env->wall[y].width, &env->wall[y].height);
		env->wall[y].buffer = (int *)mlx_get_data_addr(env->wall[y].img, \
			&env->wall[y].pixel_bits, &env->wall[y].line_bytes, &env->wall[y].endian);
		env->wall[y].line_bytes /= 4;
		y++;
	}
	env->img = mlx_new_image(env->mlx, WIN_X_SZ, WIN_Y_SZ);
	env->buffer = (int *)mlx_get_data_addr(env->img, \
		&env->pixel_bits, &env->line_bytes, &env->endian);
	env->line_bytes /= 4;
	render(env);
	mlx_hook(env->win, 2, 1L<<0, key_press_hook, env);
	mlx_hook(env->win, 3, 1L<<1, key_release_hook, env);
	mlx_hook(env->win, 4, 0L, mouse_down_hook, env);
	mlx_hook(env->win, 5, 0L, mouse_up_hook, env);
	mlx_hook(env->win, 6, 0L, mouse_move_hook, env);
	mlx_loop_hook(env->mlx, update_hook, env);
	mlx_loop(env->mlx);
	mlx_destroy_image(env->mlx, env->img);
	return (EXIT_SUCCESS);
}
