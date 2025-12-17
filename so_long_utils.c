#include "so_long.h"

static int get_map_size(int fd)
{
	int len;
	char *gnl;

	gnl = get_next_line(fd, 0);
	len = 0;
	while (gnl)
	{
		len += ft_strlen(gnl);
		free(gnl);
		gnl = get_next_line(fd, 0);
	}
	return (close(fd), len);
}

char *read_map(char *map, t_fdf *fdf)
{
	char *full_map;
	char *gnl;
	int fd;
	int len;
	int size;

	len = 0;
	fd = open(map, O_RDONLY);
	size = get_map_size(fd);
	if (fd < 0 || size <= 0)
		return (ft_printf_error("Error\nMap incorrect"), free_things(fdf, 1), NULL);
	full_map = malloc(size + 1);
	if (!full_map)
		return (close(fd), free_things(fdf, 1), NULL);
	fd = open(map, O_RDONLY);
	gnl = get_next_line(fd, 1);
	while (gnl)
	{
		ft_memcpy(&full_map[len], gnl, ft_strlen(gnl));
		len += ft_strlen(gnl);
		free(gnl);
		gnl = get_next_line(fd, 0);
	}
	return (close(fd), full_map[len] = 0, full_map);
}

int get_map_len(char *map)
{
	int i;

	i = 0;
	while (map[i] && map[i] != '\n')
		i++;
	return i;
}

int get_map_height(char *map)
{
	int i;
	int height;

	i = 0;
	height = 0;
	while (map[i])
	{
		if ((map[i] == '\n' && map[i + 1]) || !map[i])
			height++;
		i++;
	}
	return height + 1;
}

char **split_every_char(char *map)
{
	int len;
	char **split;
	int i;
	int j;

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
