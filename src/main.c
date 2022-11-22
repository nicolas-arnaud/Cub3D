/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/22 06:01:26 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Cub3d main:
 * 
 * - Verify that map is given and have the right extension and load it.
 * - If map loading failed, exit. Cleanup is handle by loader.
 * - Initialize mlx window and game.
 * - Setup mlx loop hook and start loop.
 */

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
	mlx_loop_hook(env->mlx, update_hook, env);
	mlx_loop(env->mlx);
	return (EXIT_SUCCESS);
}
