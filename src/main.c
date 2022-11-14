/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/14 10:39:10 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		return (EXIT_FAILURE);
	env = load_map(argv[1]);
	if (!env)
		return (EXIT_FAILURE);
	init_window(env);
	init_game(env);
	render(env);
	mlx_loop_hook(env->mlx, update_hook, env);
	mlx_loop(env->mlx);
	mlx_destroy_image(env->mlx, env->img);
	return (EXIT_SUCCESS);
}
