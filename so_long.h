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

//Hook
int	key_hook(int keycode, t_fdf *fdf);
int close_window(t_fdf *fdf);

//Utils
int get_map_height(char *map);
int get_map_len(char *map);
char *read_map(char *map, t_fdf *fdf);

//Check Map
void check_valid_size(t_fdf *fdf, char *map);
int check_valid_map(char *map);
int check_walls(t_fdf *fdf);

//Initialize
void init_datas(t_fdf *fdf, char *map);

//Error Handling
void free_hub(t_fdf *fdf, int value);

#endif
