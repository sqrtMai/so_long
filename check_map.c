/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/15 19:46:24 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void check_valid_size(t_fdf *fdf, char *map)
{
	int i;
	int line_size;
	int next_line_size;

	i = 0;
	line_size = get_map_len(map);
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1])
		{
			next_line_size = get_map_len(&map[i + 1]);
			if (line_size != next_line_size)
			{
				free(fdf->map->map);
				free(fdf->map);
				ft_printf("Map hasn't a valid size");
				exit(1);
			}
		}
		i++;
	}
}

int check_valid_map(char *map)
{
	int exit;
	int start;
	int collectible;
	int i;

	exit = 0;
	start = 0;
	collectible = 0;
	i = 0;
	while (map[i])
	{
		if (map[i] == 'E')
			exit = 1;
		if (map[i] == 'P')
			start = 1;
		if (map[i] == 'C')
			collectible = 1;
		if (map[i] != 'P' && map[i] != 'C' && map[i] != 'E' && map[i] != '1' && map[i] != '0' && map[i] != '\n')
			return 0;
		i++;
	}
	if (start > 1 || exit > 1)
		return 0;
	return (exit + start + collectible);
}

int check_walls(t_fdf *fdf)
{
	int i;
	int y;

	i = 0;
	while (i < fdf->map->map_height)
	{
		y = 0;
		while (y < fdf->map->map_len)
		{
			if (i == 0 && fdf->map->points[i][y].type != '1')
					return (ft_printf("The map is invalid."), free_hub(fdf, 1), -1);
			if ((i > 0 && i < fdf->map->map_height - 1) &&
				fdf->map->points[i][0].type != '1' || fdf->map->points[i][fdf->map->map_len - 1].type != '1')
					return (ft_printf("The map is invalid."), free_hub(fdf, 1), -1);
			if (i == fdf->map->map_height - 1 && fdf->map->points[i][y].type != '1')
					return (ft_printf("The map is invalid."), free_hub(fdf, 1), -1);
			y++;
		}
		i++;
	}
	return 1;
}
