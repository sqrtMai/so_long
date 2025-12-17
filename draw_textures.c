/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 16:11:19 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	*find_player(t_fdf *fdf)
{
	int	i;
	int	y;

	i = 0;
	while (i < fdf->map->map_height)
	{
		y = 0;
		while (y < fdf->map->map_len)
		{
			if (fdf->map->points[i][y].type == 'P')
				return (&fdf->map->points[i][y]);
			y++;
		}
		i++;
	}
	return (&fdf->map->points[i][y]);
}

int	draw_player(t_fdf *fdf)
{
	return (mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->s3,
			find_player(fdf)->z, find_player(fdf)->l));
}

void	print_case(t_fdf *fdf, char c, int z, int l)
{
	if (c == '0')
	{
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->s1, z, l);
		z += 75;
	}
	else if (c == '1')
	{
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->s2, z, l);
		z += 75;
	}
	else if (c == 'P')
	{
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->s3, z, l);
		z += 75;
	}
	else if (c == 'C')
	{
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->s4, z, l);
		z += 75;
	}
	else if (c == 'E')
	{
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->s5, z, l);
		z += 75;
	}
}

void	print_map(t_fdf *fdf)
{
	int	y;
	int	i;
	int	z;
	int	l;

	i = 0;
	l = 0;
	while (i < fdf->map->map_height)
	{
		y = 0;
		z = 0;
		while (y < fdf->map->map_len)
		{
			print_case(fdf, fdf->map->points[i][y].type, z, l);
			fdf->map->points[i][y].z = z;
			fdf->map->points[i][y].l = l;
			z += 75;
			y++;
		}
		l += 75;
		i++;
	}
}
