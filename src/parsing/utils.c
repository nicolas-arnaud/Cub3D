/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:29:26 by narnaud           #+#    #+#             */
/*   Updated: 2022/08/23 16:21:21 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
			ret |= ft_atoi(colors[i++]) << (8 * (2 - c++));
		else
		{
			ft_free_split(colors);
			i = 0;
			colors = ft_split(*(++rgb), ',');
		}
	}
	ft_free_split(colors);
	return (ret);
}
