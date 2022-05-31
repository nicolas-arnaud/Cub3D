/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/31 09:13:28 by narnaud          ###   ########.fr       */
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

void	draw_square(t_env *env, t_vec vec, int size, int color)
{
	int	step_x;
	int	step_y;

	step_y = 0;
	while (step_y < size)
	{
		step_x = 0;
		while (step_x < size)
		{
			env->buffer[(env->line_bytes * (vec.y * size + step_y)) + (vec.x * size + step_x)] = color;
			step_x++;
		}
		step_y++;
	}
}

void	render_minimap(t_env *env)
{
	char	**map;
	t_vec	vec;

	vec.y = 0;
	map = env->map;
	while (map[vec.y])
	{
		vec.x = 0;
		while (map[vec.y][vec.x])
		{
			if (map[vec.y][vec.x] == '0')		
				draw_square(env, vec, 6, 39424);
			else if (map[vec.y][vec.x] == '1')
				draw_square(env, vec, 6, 10420483);
			vec.x++;
		}
		vec.y++;
	}
	vec.x = round(env->playerPos.x);
	vec.y = round(env->playerPos.y);
	draw_square(env, vec, 6, 255);
}

void render_view(t_env *env)
{
	(void)env;
}

int key_hook_primary(int keycode, void *param)
{	
	t_env *env;

	env = (t_env *)param;
	env->img = mlx_new_image(env->mlx, WIN_X_SZ, WIN_Y_SZ);
	env->buffer = (int *)mlx_get_data_addr(env->img, \
		&env->pixel_bits, &env->line_bytes, &env->endian);
	env->line_bytes /= 4;
	if (keycode == KEY_ARROW_UP)
		set_vec(&env->playerPos, env->playerPos.x + env->playerDir.x, env->playerPos.y + env->playerDir.y);
	else if (keycode == KEY_ARROW_DOWN)
		set_vec(&env->playerPos, env->playerPos.x - env->playerDir.x, env->playerPos.y - env->playerDir.y);
	else if (keycode == KEY_ARROW_LEFT)
	{
		 set_vec(&env->playerDir,
				 cos(-M_PI / 2) * env->playerDir.x - sin(-M_PI / 2) * env->playerDir.y,
				 sin(-M_PI / 2) * env->playerDir.x + cos(-M_PI / 2) * env->playerDir.y);
	}
	else if (keycode == KEY_ARROW_RIGHT)
	{
		 set_vec(&env->playerDir,
				 cos(M_PI / 2) * env->playerDir.x - sin(M_PI / 2) * env->playerDir.y,
				 sin(M_PI / 2) * env->playerDir.x + cos(M_PI / 2) * env->playerDir.y);
	}
	render_minimap(env);
	render_view(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
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
	mlx_key_hook(env->win, key_hook_primary, env);
	mlx_loop(env->mlx);
	return (EXIT_SUCCESS);
}
