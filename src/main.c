/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/14 16:35:36 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		return (printf("Usage: ./cub3d mapfile.cub\n"), EXIT_FAILURE);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (printf("Wrong map file extension"), EXIT_FAILURE);
	env = load_map(argv[1]);
	if (!env)
		return (EXIT_FAILURE);
	init_window(env);
	if (init_game(env) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	render(env);
	mlx_loop_hook(env->mlx, update_hook, env);
	mlx_loop(env->mlx);
	mlx_destroy_image(env->mlx, env->img);
	return (EXIT_SUCCESS);
}
