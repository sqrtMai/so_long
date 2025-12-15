#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <math.h>
# include "mlx_linux/mlx.h"
# include <limits.h>

typedef struct s_point
{
    int x;
    int y;
    char type;
}   t_point;

typedef struct s_map
{
	t_point **points;
	int map_len;
	int map_height;
    char *map;
}	t_map;

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     width;
    int     height;

}				t_image;

typedef struct s_fdf
{
    void    *mlx;
    void    *window;
    t_map   *map;
    t_image   img;
} t_fdf;

int close_window(t_fdf *fdf);
int	key_hook(int keycode, t_fdf *fdf);
void draw_points(t_fdf *fdf);
void draw_map(t_fdf *fdf);
void init_datas(t_fdf *fdf, char *map);
int check_valid_size(t_fdf *fdf, char *map);
int get_map_height(char *map);
int get_map_len(char *map);
char *read_map(char *map);
void init_window(t_fdf *fdf);
#endif
