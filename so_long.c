#include "so_long.h"

int main(int argc, char **argv)
{
	t_fdf fdf;

	if (argc != 2 || !argv[1])
		return 0;
	if ((ft_findstr(argv[1], ".ber")) == 0)
		return (ft_printf("Wrong extension file extension"), 1);
	init_datas(&fdf, argv[1]);
	return 0;
}
