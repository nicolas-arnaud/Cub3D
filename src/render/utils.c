/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:45:14 by narnaud           #+#    #+#             */
/*   Updated: 2022/08/23 16:05:12 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_rectangle(t_env *env, t_rect rect, int borders)
{
	t_vec	step;

	step.y = 0;
	while (step.y < rect.size.y)
	{
		step.x = 0;
		while (step.x < rect.size.x)
		{
			if (borders && \
					(step.x == rect.size.x - 1 || step.y == rect.size.y - 1))
				env->buffer[(env->line_bytes * (int)(rect.start.y + step.y)) \
				+ (int)(rect.start.x + step.x)] = 0;
			else
				env->buffer[(env->line_bytes * (int)(rect.start.y + step.y)) \
				+ (int)(rect.start.x + step.x)] = rect.color;
			step.x++;
		}
		step.y++;
	}
}
