/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 16:39:27 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_extension(char *argv)
{
	int	i;

	i = 0;
	if (!argv)
		exit(1);
	while (argv[i] && argv[i] != '.')
		i++;
	if (argv[i] == '.')
	{
		if ((ft_findstr(&argv[i], ".ber") == 1))
			return (ft_printf_error("Error\nWrong file extension"),
				exit(1));
	}
	else if (!argv[i])
	{
		ft_printf_error("Error\nWrong file extension");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2 || !argv[1])
		return (0);
	check_extension(argv[1]);
	fdf.fd = open(argv[1], O_RDONLY);
	if (fdf.fd < 0)
		return (ft_printf_error("Error\nCouldn't find the map"), exit(1), 1);
	init_datas(&fdf, argv[1]);
	return (0);
}

/*TODO régler le pb de uninitialised value
régler le problème de mon check map
quand une map est pas valide ça call destroy things
sur des valeur non initiée*/
