/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 16:11:22 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_point	**malloc_map(t_fdf *fdf)
{
	int		i;
	t_point	**points;

	i = 0;
	points = malloc(sizeof(t_point *) * fdf->map->map_height);
	if (!points)
		return (free_things(fdf, 0), NULL);
	while (i < fdf->map->map_height)
	{
		points[i] = malloc(sizeof(t_point) * (fdf->map->map_len));
		if (!points[i])
			return (free_things(fdf, i), NULL);
		i++;
	}
	return (points);
}

void	put_datas_to_point(t_fdf *fdf)
{
	int		i;
	int		y;
	char	**split;

	i = 0;
	split = ft_split(fdf->map->map, "\n");
	if (!split)
		return (free_things(fdf, 0));
	fdf->map->points = malloc_map(fdf);
	while (split[i])
	{
		y = 0;
		while (split[i][y] && split[i])
		{
			fdf->map->points[i][y].type = split[i][y];
			if (split[i][y] == 'C')
				fdf->map->collectibles++;
			fdf->map->points[i][y].x = y;
			fdf->map->points[i][y].y = i;
			y++;
		}
		i++;
	}
	free_everything((void **)split);
	check_walls(fdf);
}
