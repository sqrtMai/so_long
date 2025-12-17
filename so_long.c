#include "so_long.h"

int main(int argc, char **argv)
{
	t_fdf fdf;

	if (argc != 2 || !argv[1])
		return 0;
	if ((ft_findstr(argv[1], ".ber")) == 0)
		return (ft_printf_error("Error\nWrong extension file extension"), 1);
	init_datas(&fdf, argv[1]);
	return 0;
}

/*TODO régler le pb de uninitialised value
régler le problème de mon check map
quand une map est pas valide ça call destroy things
sur des valeur non initiée*/

