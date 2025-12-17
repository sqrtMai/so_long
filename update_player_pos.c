/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 13:44:17 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void update_player_right(t_fdf *fdf)
{
	t_point *player = find_player(fdf);

	fdf->map->moves++;
	ft_printf("Move : %d\n", fdf->map->moves);
	if (fdf->map->points[player->y][player->x + 1].type != '1')
	{
		if (fdf->map->points[player->y][player->x + 1].type == 'C')
		{
			fdf->map->collectibles--;
			fdf->map->points[player->y][player->x + 1].type = '0';
		}
		if (fdf->map->points[player->y][player->x + 1].type == 'E' && !fdf->map->collectibles)
			free_things(fdf, -1);
		if (fdf->map->points[player->y][player->x].type == 'E')
			mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite5, (player->z), player->l);
		else
			mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite1, player->z, player->l);
		player->x++;

		player->z += 75;
	}
}

void update_player_left(t_fdf *fdf)
{
	t_point *player = find_player(fdf);

	fdf->map->moves++;
	ft_printf("Move : %d\n", fdf->map->moves);
	if (fdf->map->points[player->y][player->x - 1].type != '1')
	{
		if (fdf->map->points[player->y][player->x - 1].type == 'C')
		{
			fdf->map->collectibles--;
			fdf->map->points[player->y][player->x - 1].type = '0';
		}
		if (fdf->map->points[player->y][player->x - 1].type == 'E' && !fdf->map->collectibles)
			free_things(fdf, -1);
		if (fdf->map->points[player->y][player->x].type == 'E')
			mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite5, (player->z), player->l);
		else
			mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite1, player->z, player->l);
		player->x--;
		player->z -= 75;
	}
}

void update_player_up(t_fdf *fdf)
{
	t_point *player = find_player(fdf);

	fdf->map->moves++;
	ft_printf("Move : %d\n", fdf->map->moves);
	if (fdf->map->points[player->y - 1][player->x].type != '1')
	{
		if (fdf->map->points[player->y - 1][player->x].type == 'C')
		{
			fdf->map->collectibles--;
			fdf->map->points[player->y - 1][player->x].type = '0';
		}
		if (fdf->map->points[player->y - 1][player->x].type == 'E' && !fdf->map->collectibles)
			free_things(fdf, -1);
		if (fdf->map->points[player->y][player->x].type == 'E')
			mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite5, player->z, (player->l));
		else
			mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite1, player->z, player->l);
		player->y--;
		player->l -= 75;
	}
}

void update_player_down(t_fdf *fdf)
{
	t_point *player = find_player(fdf);

	fdf->map->moves++;
	ft_printf("Move : %d\n", fdf->map->moves);
	if (fdf->map->points[player->y + 1][player->x].type != '1')
	{
		if (fdf->map->points[player->y + 1][player->x].type == 'C')
		{
			fdf->map->collectibles--;
			fdf->map->points[player->y + 1][player->x].type = '0';
		}
		if (fdf->map->points[player->y + 1][player->x].type == 'E' && !fdf->map->collectibles)
			free_things(fdf, -1);
		if (fdf->map->points[player->y][player->x].type == 'E')
			mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite5, player->z, (player->l));
		else
			mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite1, player->z, player->l);
		player->y++;

		player->l += 75;
	}
}
