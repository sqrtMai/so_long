/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 16:18:54 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	invalid_error_message(t_fdf *fdf)
{
	ft_printf_error("Error\nThe map is invalid.");
	free_things(fdf, -1);
}

void	not_solvable_error_message(t_fdf *fdf)
{
	ft_printf_error("Error\nThe map isn't solvable.");
	free_things(fdf, -1);
}

void	destroy_things(t_fdf *fdf)
{
	if (fdf->sprites)
	{
		if (fdf->sprites->s1)
			mlx_destroy_image(fdf->mlx, fdf->sprites->s1);
		if (fdf->sprites->s2)
			mlx_destroy_image(fdf->mlx, fdf->sprites->s2);
		if (fdf->sprites->s3)
			mlx_destroy_image(fdf->mlx, fdf->sprites->s3);
		if (fdf->sprites->s4)
			mlx_destroy_image(fdf->mlx, fdf->sprites->s4);
		if (fdf->sprites->s5)
			mlx_destroy_image(fdf->mlx, fdf->sprites->s5);
	}
	if (fdf->mlx)
	{
		mlx_destroy_window(fdf->mlx, fdf->window);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
}

void	free_things(t_fdf *fdf, int value)
{
	int	i;

	i = 0;
	if (value < 0)
		value = fdf->map->map_height;
	if (fdf->map)
	{
		if (fdf->map->map)
			free(fdf->map->map);
		if (fdf->map->split_copy)
			free_everything((void **)fdf->map->split_copy);
		if (fdf->map->points)
		{
			while (i < value)
				free(fdf->map->points[i++]);
			free(fdf->map->points);
		}
		free(fdf->map);
		if (fdf->sprites)
		{
			destroy_things(fdf);
			free(fdf->sprites);
		}
	}
	exit(1);
}
