/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:14:08 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/22 03:04:16 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_rect	get_mm_cell(char type, t_vec pos, t_vec delta)
{
	if (type == '1')
		return ((t_rect){vec_mult(pos, delta), delta, 0x00009F});
	else if (type == '2')
		return ((t_rect){vec_mult(pos, delta), delta, 0x9F709F});
	else
		return ((t_rect){vec_mult(pos, delta), delta, 0x009F00});
}

t_mmap	measure(t_env *env)
{
	t_mmap	ret;

	ret.delt = (t_vec){4, 4};
	ret.min = (t_vec){ft_max(env->player_pos.x - 25, 0),
		ft_max(env->player_pos.y - 25, 0)};
	ret.max = (t_vec){
		ft_min(ft_max(env->player_pos.x + 25, ret.min.x + 50), env->wide),
		ft_min(ft_max(env->player_pos.y + 25, ret.min.y + 50), env->deep)};
	return (ret);
}

void	render_minimap(t_env *env, t_mmap mm)
{
	t_vec		pos;

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
	draw_rectangle(env, (t_rect){
		(t_vec){(env->player_pos.x - mm.min.x) * mm.delt.x - 1,
		(env->player_pos.y - mm.min.y) * mm.delt.y - 1},
		(t_vec){mm.delt.x / 2, mm.delt.y / 2}, 0xFF0000}, 0);
}
