/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 16:11:22 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_map_size(int fd)
{
	int		len;
	char	*gnl;

	gnl = get_next_line(fd, 0);
	if (!gnl)
		return (0);
	len = 0;
	while (gnl)
	{
		len += ft_strlen(gnl);
		free(gnl);
		gnl = get_next_line(fd, 0);
	}
	return (close(fd), len);
}

char	*read_map(char *map, t_fdf *fdf)
{
	char	*full_map;
	char	*gnl;
	int		len;
	int		size;

	len = 0;
	size = get_map_size(fdf->fd);
	if (size <= 0)
		return (ft_printf_error("Error\nMap incorrect"), NULL);
	full_map = malloc(size + 1);
	if (!full_map)
		return (close(fdf->fd), NULL);
	fdf->fd = open(map, O_RDONLY);
	gnl = get_next_line(fdf->fd, 1);
	while (gnl)
	{
		ft_memcpy(&full_map[len], gnl, ft_strlen(gnl));
		len += ft_strlen(gnl);
		free(gnl);
		gnl = get_next_line(fdf->fd, 0);
	}
	return (close(fdf->fd), full_map[len] = 0, full_map);
}

int	get_map_len(char *map)
{
	int	i;

	i = 0;
	while (map[i] && map[i] != '\n')
		i++;
	return (i);
}

int	get_map_height(char *map)
{
	int	i;
	int	height;

	i = 0;
	height = 0;
	while (map[i])
	{
		if ((map[i] == '\n' && map[i + 1]) || !map[i])
			height++;
		i++;
	}
	return (height + 1);
}

char	**split_every_char(char *map)
{
	int		len;
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(map) - get_map_height(map);
	split = malloc((len + 1) * sizeof(char *));
	while (split[i] && map[j])
	{
		if (map[j] == '\n')
			j++;
		split[i] = malloc(1 + 1);
		split[i][1] = 0;
		split[i][0] = map[j];
		i++;
		j++;
	}
	return (split[len] = 0, split);
}
