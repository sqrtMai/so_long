/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 16:43:28 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_sprites(t_fdf *fdf)
{
	fdf->sprites->s1 = mlx_xpm_file_to_image(fdf->mlx,
			"textures/TILE.xpm", &fdf->sprites->s_size, &fdf->sprites->s_size);
	if (!fdf->sprites->s1)
		return (ft_printf_error("Error\nTILE.xpm not found"),
			free_things(fdf, -1));
	fdf->sprites->s2 = mlx_xpm_file_to_image(fdf->mlx, "textures/WALL.xpm",
			&fdf->sprites->s_size, &fdf->sprites->s_size);
	if (!fdf->sprites->s2)
		return (ft_printf_error("Error\nWALL.xpm not found"),
			free_things(fdf, -1));
	fdf->sprites->s3 = mlx_xpm_file_to_image(fdf->mlx, "textures/BABA.xpm",
			&fdf->sprites->s_size, &fdf->sprites->s_size);
	if (!fdf->sprites->s3)
		return (ft_printf_error("Error\nBABA.xpm not found"),
			free_things(fdf, -1));
	fdf->sprites->s4 = mlx_xpm_file_to_image(fdf->mlx, "textures/ORB.xpm",
			&fdf->sprites->s_size, &fdf->sprites->s_size);
	if (!fdf->sprites->s4)
		return (ft_printf_error("Error\nORB.xpm not found"),
			free_things(fdf, -1));
	fdf->sprites->s5 = mlx_xpm_file_to_image(fdf->mlx, "textures/FLAG.xpm",
			&fdf->sprites->s_size, &fdf->sprites->s_size);
	if (!fdf->sprites->s5)
		return (ft_printf_error("Error\nFLAG.xpm not found"),
			free_things(fdf, -1));
}

static void	init_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, fdf->map->map_len * 75,
			fdf->map->map_height * 75, "so_long");
	fdf->img.width = 75;
	fdf->img.height = 75;
	mlx_hook(fdf->window, 3, 1L << 1, key_hook, fdf);
	mlx_hook(fdf->window, 17, 0, close_window, fdf);
	init_sprites(fdf);
	print_map(fdf);
	mlx_loop_hook(fdf->mlx, draw_player, fdf);
	mlx_loop(fdf->mlx);
}

static void	init_to_null(t_fdf *fdf, int i)
{
	if (i == 1)
	{
		fdf->map->moves = 0;
		fdf->map->collectibles = 0;
		fdf->map->flood_fill = 0;
		fdf->map->map = NULL;
		fdf->map->split_copy = NULL;
		fdf->sprites = NULL;
		fdf->map->points = NULL;
		fdf->mlx = NULL;
		fdf->window = NULL;
	}
	if (i == 2)
	{
		if (fdf->sprites)
		{
			fdf->sprites->s_size = 0;
			fdf->sprites->s1 = NULL;
			fdf->sprites->s2 = NULL;
			fdf->sprites->s3 = NULL;
			fdf->sprites->s4 = NULL;
			fdf->sprites->s5 = NULL;
		}
	}
}

static void	init_struct(t_fdf *fdf, char *map)
{
	fdf->map = malloc(sizeof(t_map));
	if (!fdf->map)
		exit(1);
	init_to_null(fdf, 1);
	fdf->map->map = read_map(map, fdf);
	if (!fdf->map->map)
		return (close(fdf->fd), free(fdf->map), exit(1));
	check_valid_size(fdf, fdf->map->map);
	fdf->map->map_height = get_map_height(fdf->map->map);
	fdf->map->map_len = get_map_len(fdf->map->map);
	if (fdf->map->map_len * 70 > 2560 || fdf->map->map_height * 70 > 1440)
		return (ft_printf_error("Error\nThe map is too big for the screen"),
			free_things(fdf, 0));
	if ((fdf->map->map_len < 3 || fdf->map->map_height < 3)
		|| (fdf->map->map_len == 3 && fdf->map->map_height < 6)
		|| (fdf->map->map_height == 3 && fdf->map->map_len < 6))
		return (ft_printf_error("Error\nThe map doesn't have a correct size"),
			free_things(fdf, 0));
	if (check_valid_map(fdf->map->map) != 3)
		return (ft_printf("Error\nWrong requierments"), free_things(fdf, 0));
	fdf->map->split_copy = ft_split(fdf->map->map, "\n");
	fdf->map->size.x = fdf->map->map_len;
	fdf->map->size.y = fdf->map->map_height;
	fdf->sprites = malloc(sizeof(t_sprite));
	init_to_null(fdf, 2);
}

void	init_datas(t_fdf *fdf, char *map)
{
	init_struct(fdf, map);
	put_datas_to_point(fdf);
	init_window(fdf);
}
