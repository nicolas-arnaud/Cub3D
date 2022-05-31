/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:59:01 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/31 12:22:41 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	vec_len(t_vec_d vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

void	set_vec(t_vec_d *vec, double x, double y)
{
	vec->x = x;
	vec->y = y;
}

int	rgb_to_int(char	**rgb)
{
	int		ret;
	int		i;
	int		c;
	char	**colors;

	ret = 0;
	rgb++;
	colors = ft_split(*rgb, ',');
	c = 0;
	i = 0;
	while (c < 3)
	{
		if (colors[i])
		{
			ret |= ft_atoi(colors[i]) << (8 * (2 - c));
			c++;
			i++;
		}
		else
		{
			ft_free_split(colors);
			rgb++;
			i = 0;
			colors = ft_split(*rgb, ',');
		}
	}
	ft_free_split(colors);
	return (ret);
}
