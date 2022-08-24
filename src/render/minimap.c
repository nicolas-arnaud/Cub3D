/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:14:08 by narnaud           #+#    #+#             */
/*   Updated: 2022/08/23 16:01:38 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_rect	get_mm_cell(char type, t_vec pos, t_vec delta)
{
	int		color;

	if (type == '0')
		color = 0x009F00;
	else if (type == '1')
		color = 0x00009F;
	else if (type == '2')
		color = 0x9F709F;
	else
		color = 0x000000;
	return ((t_rect){vec_mult(pos, delta), delta, color});
}

void	render_minimap(t_env *env, t_vec size)
{
	char	**map;
	t_vec	pos;
	t_vec	delt;

	vec_set(&delt, size.x / env->wide, size.y / env->deep);
	pos.y = 0;
	map = env->map;
	while (map[pos.y])
	{
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			draw_rectangle(env, get_mm_cell(map[pos.y][pos.x], pos, delt), 1);
			pos.x++;
		}
		pos.y++;
	}
	draw_rectangle(env, (t_rect){\
		(t_vec){env->playerPos.x * delt.x - delt.x / 4.0, \
		env->playerPos.y * delt.y - delt.y / 4.0}, \
		(t_vec){delt.x / 2, delt.y / 2}, 0xFF0000}, 0);
}
