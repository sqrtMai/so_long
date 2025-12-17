/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 14:44:14 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <math.h>
# include "mlx_linux/mlx.h"
# include <limits.h>

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		l;
	char	type;
}	t_point;

typedef struct s_map
{
	t_point	**points;
	t_point	size;
	int		map_len;
	int		map_height;
	char	*map;
	char	**split_copy;
	int		collectibles;
	int		collectibles_taken;
	int		flood_fill;
	int		moves;
}	t_map;

typedef struct s_sprite
{
	void	*s1;
	void	*s2;
	void	*s3;
	void	*s4;
	void	*s5;
	int		s_size;
}	t_sprite;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_fdf
{
	void		*mlx;
	void		*window;
	int			fd;
	t_map		*map;
	t_image		img;
	t_sprite	*sprites;
}				t_fdf;

//Hook
int		key_hook(int keycode, t_fdf *fdf);
int		close_window(t_fdf *fdf);

//Utils
int		get_map_height(char *map);
int		get_map_len(char *map);
char	*read_map(char *map, t_fdf *fdf);
char	**split_every_char(char *map);
void	put_datas_to_point(t_fdf *fdf);
t_point	*find_player(t_fdf *fdf);

//Check Map
int		check_valid_map(char *map);
void	check_valid_size(t_fdf *fdf, char *map);
void	check_walls(t_fdf *fdf);

//Initialize
void	init_datas(t_fdf *fdf, char *map);

//Error Handling
void	free_things(t_fdf *fdf, int value);
void	invalid_error_message(t_fdf *fdf);
void	not_solvable_error_message(t_fdf *fdf);

//Update Player Position
void	update_player_right(t_fdf *fdf);
void	update_player_left(t_fdf *fdf);
void	update_player_up(t_fdf *fdf);
void	update_player_down(t_fdf *fdf);

//Draw Textures
void	print_map(t_fdf *fdf);
int		draw_player(t_fdf *fdf);

#endif
