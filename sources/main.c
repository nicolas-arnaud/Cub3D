/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/06/01 13:49:31 by narnaud          ###   ########.fr       */
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
				env->wallTexture[0], env->wallTexture[1],\
				env->wallTexture[2], env->wallTexture[3]);
		printf("\e[1;32m========================\e[0m\n");
		printf("=> Floor color: %d\n=> Ceil color: %d\n", env->floorColor, env->ceilColor);
		printf("\e[1;32m========> MAP <========\e[0m\n");
		y = 0;
		while (env->map[y])
			printf("%s\n", env->map[y++]);
	}
	init_window(env);
	render(env);
	mlx_hook(env->win, 2, 1L<<0, key_press_hook, env);
	mlx_hook(env->win, 3, 1L<<1, key_release_hook, env);
	mlx_loop_hook(env->mlx, update_hook, env);
	mlx_loop(env->mlx);
	return (EXIT_SUCCESS);
}
