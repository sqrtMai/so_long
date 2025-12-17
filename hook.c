/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 16:11:21 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_fdf *fdf)
{
	free_things(fdf, -1);
	return (0);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	fdf->map->collectibles_taken = 0;
	if (keycode == 65307)
		close_window(fdf);
	if (keycode == 65363)
		update_player_right(fdf);
	if (keycode == 65361)
		update_player_left(fdf);
	if (keycode == 65362)
		update_player_up(fdf);
	if (keycode == 65364)
		update_player_down(fdf);
	return (0);
}
