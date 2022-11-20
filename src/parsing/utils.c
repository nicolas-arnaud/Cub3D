/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:29:26 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/14 12:12:58 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**next_split(int *i, char **colors, char ***rgb)
{
	if (!colors[*i])
	{
		ft_free_split(colors);
		if (++(*rgb))
			colors = ft_split(**rgb, ',');
		*i = 0;
	}
	return (colors);
}

int	rgb_to_int(char	**rgb)
{
	int		ret;
	int		i;
	int		c;
	char	**colors;
	int		color;

	c = 0;
	i = 0;
	ret = 0;
	colors = ft_split(*rgb, ',');
	while (c < 3 && rgb && colors)
	{
		colors = next_split(&i, colors, &rgb);
		if (!colors || !colors[i])
			continue ;
		color = ft_atoi(colors[i++]);
		if (color >= 0 && color < 256)
			ret |= color << (8 * (2 - c++));
	}
	if (c < 3)
		return (printf("Error:\nInvalid color.\n"), -1);
	return (ft_free_split(colors), ret);
}
