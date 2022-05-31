/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/31 17:13:28 by narnaud          ###   ########.fr       */
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

int key_hook_primary(int keycode, void *param)
{	
	t_env *env;

	env = (t_env *)param;
	if (keycode == KEY_ARROW_UP)
	{
		if (env->map[(int)env->playerPos.y][(int)(env->playerPos.x + env->playerDir.x / 5)] == '0')
			set_vec(&env->playerPos, env->playerPos.x + env->playerDir.x / 5, env->playerPos.y);
		if (env->map[(int)(env->playerPos.y + env->playerDir.y / 5)][(int)env->playerPos.x] == '0')
			set_vec(&env->playerPos, env->playerPos.x, env->playerPos.y + env->playerDir.y / 5);
	}
	else if (keycode == KEY_ARROW_DOWN)
	{
		if (env->map[(int)env->playerPos.y][(int)(env->playerPos.x - env->playerDir.x / 5)] == '0')
			set_vec(&env->playerPos, env->playerPos.x - env->playerDir.x / 5, env->playerPos.y);
		if (env->map[(int)(env->playerPos.y - env->playerDir.y / 5)][(int)env->playerPos.x] == '0')
			set_vec(&env->playerPos, env->playerPos.x, env->playerPos.y - env->playerDir.y / 5);
	}
	if (keycode == KEY_ARROW_LEFT)
	{
		 set_vec(&env->playerDir,
				 cos(-M_PI / 9) * env->playerDir.x - sin(-M_PI / 9) * env->playerDir.y,
				 sin(-M_PI / 9) * env->playerDir.x + cos(-M_PI / 9) * env->playerDir.y);
		 set_vec(&env->camPlan,
				 cos(-M_PI / 9) * env->camPlan.x - sin(-M_PI / 9) * env->camPlan.y,
				 sin(-M_PI / 9) * env->camPlan.x + cos(-M_PI / 9) * env->camPlan.y);
	}
	else if (keycode == KEY_ARROW_RIGHT)
	{
		 set_vec(&env->playerDir,
				 cos(M_PI / 9) * env->playerDir.x - sin(M_PI / 9) * env->playerDir.y,
				 sin(M_PI / 9) * env->playerDir.x + cos(M_PI / 9) * env->playerDir.y);
		 set_vec(&env->camPlan,
				 cos(M_PI / 9) * env->camPlan.x - sin(M_PI / 9) * env->camPlan.y,
				 sin(M_PI / 9) * env->camPlan.x + cos(M_PI / 9) * env->camPlan.y);
	}
	if (DEBUG)
	{
	printf("playerPos: %f, %f. playerDir: %f, %f\n", env->playerPos.x, env->playerPos.y, env->playerDir.x, env->playerDir.y);
	printf("camPlan: %f, %f\n", env->camPlan.x, env->camPlan.y);
	}
	render(env);
	return (1);
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
	mlx_key_hook(env->win, key_hook_primary, env);
	mlx_loop(env->mlx);
	return (EXIT_SUCCESS);
}
