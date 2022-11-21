/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:14:08 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/21 23:33:25 by narnaud          ###   ########.fr       */
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

typedef struct s_minimap
{
	t_vec	min;
	t_vec	max;
	t_vec	delt;
}	t_minimap;

t_minimap	measure(t_env *env)
{
	t_minimap	ret;

	ret.delt = (t_vec){4, 4};
	ret.min = (t_vec){ft_max(env->player_pos.x - 25, 0),
		ft_max(env->player_pos.y - 25, 0)};
	ret.max = (t_vec){
		ft_min(ft_max(env->player_pos.x + 25, ret.min.x + 50), env->wide),
		ft_min(ft_max(env->player_pos.y + 25, ret.min.y + 50), env->deep)};
	return (ret);
}

void	render_minimap(t_env *env)
{
	t_vec		pos;
	t_minimap	mm;

	mm = measure(env);
	pos.y = 0;
	while (pos.y + mm.min.y < mm.max.y && env->map[pos.y + mm.min.y])
	{
		pos.x = 0;
		while (pos.x + mm.min.x < mm.max.x
			&& env->map[pos.y + mm.min.y][pos.x + mm.min.x])
		{
			draw_rectangle(env,
				get_mm_cell(env->map[pos.y + mm.min.y][pos.x + mm.min.x],
					pos, mm.delt), 1);
			pos.x++;
		}
		pos.y++;
	}
	draw_rectangle(env, (t_rect){\
		(t_vec){(env->player_pos.x - mm.min.x) * mm.delt.x - 1,
		(env->player_pos.y - mm.min.y) * mm.delt.y - 1},
		(t_vec){mm.delt.x / 2, mm.delt.y / 2}, 0xFF0000}, 0);
}
