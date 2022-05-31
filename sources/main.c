/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/31 07:54:29 by narnaud          ###   ########.fr       */
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
/*
void	launch_game(){

}
*/

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
	draw_square(env, env->playerPos, 6, 255);
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
	env->img = mlx_new_image(env->mlx, WIN_X_SZ, WIN_Y_SZ);
	env->buffer = (int *)mlx_get_data_addr(env->img, \
		&env->pixel_bits, &env->line_bytes, &env->endian);
	env->line_bytes /= 4;
	//launch_game(env);
	render_minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	//mlx_key_hook(env->win, key_hook_primary, env);
	mlx_loop(env->mlx);
	return (EXIT_SUCCESS);
}
