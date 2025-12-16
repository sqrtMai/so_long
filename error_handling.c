/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/16 22:20:54 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void destroy_things(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->sprites->sprite1);
	mlx_destroy_image(fdf->mlx, fdf->sprites->sprite2);
	mlx_destroy_image(fdf->mlx, fdf->sprites->sprite3);
	mlx_destroy_image(fdf->mlx, fdf->sprites->sprite4);
	mlx_destroy_image(fdf->mlx, fdf->sprites->sprite5);
	mlx_destroy_window(fdf->mlx, fdf->window);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
}
void free_things(t_fdf *fdf, int value)
{
	int i;

	i = 0;
	if (value < 0)
		value = fdf->map->map_height;
	destroy_things(fdf);
	if (fdf->map)
	{
		if (fdf->map->map)
			free(fdf->map->map);
		free_everything((void **)fdf->map->split_copy);
		if (fdf->map->points)
		{
			while (i < value)
				free(fdf->map->points[i++]);
			free(fdf->map->points);
		}
		if (fdf->sprites)
			free(fdf->sprites);
		free(fdf->map);
	}

	exit(1);
}
