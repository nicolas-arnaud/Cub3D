/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:59:01 by narnaud           #+#    #+#             */
/*   Updated: 2022/08/23 11:34:18 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	vec_set(t_vec *vec, int x, int y)
{
	vec->x = x;
	vec->y = y;
}

t_vec	vec_mult(t_vec v1, t_vec v2)
{
	return ((t_vec){v1.x * v2.x, v1.y * v2.y});
}

double	dvec_len(t_dvec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

void	dvec_set(t_dvec *vec, double x, double y)
{
	vec->x = x;
	vec->y = y;
}

t_dvec	dvec_rot(t_dvec vec, double rad, double init_len)
{
	double	len;
	t_dvec	ret;

	len = dvec_len(vec);
	ret.x = (cos(rad) * vec.x - sin(rad) * vec.y) * init_len / len;
	ret.y = (sin(rad) * vec.x + cos(rad) * vec.y) * init_len / len;
	return (ret);
}
