/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/15 20:00:29 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_hub(t_fdf *fdf, int value)
{
	int i;

	i = 0;
	if (value < 0)
		value = fdf->map->map_height;
	if (fdf->map)
	{
		if (fdf->map->map)
			free(fdf->map->map);
		if (fdf->map->points)
		{
			while (i < value)
				free(fdf->map->points[i++]);
			free(fdf->map->points);
		}
		free(fdf->map);
	}
	exit(1);
}
