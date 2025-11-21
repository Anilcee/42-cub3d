#include "cub3d.h"
#include "libft/libft.h"
#include <unistd.h>

void	exit_with_error(char *msg)
{
	write(2,msg,ft_strlen(msg));
	exit (1);
}

void	check_file(char *file)
{
	char *file_path;
	file_path = file + ft_strlen(file) - 4;
	if (ft_strncmp(file_path, ".cub", 4) != 0)
	{
		ft_printf("Error: Invalid file extension must be .cub \n");
		exit(EXIT_FAILURE);
	}
	open_file(file);
}

int	open_file(const char *file_path)
{
	int	fd;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error opening file\n");
	return (fd);
}

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || 
			c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	find_max_width(t_map *map)
{
	int	max_width;
	int	current_width;
	int	y;

	max_width = 0;
	y = 0;
	while (y < map->rows)
	{
		current_width = ft_strlen(map->map[y]);
		if (current_width > max_width)
			max_width = current_width;
		y++;
	}
	return (max_width);
}

static void	normalize_map(t_map *map)
{
	int		max_width;
	int		y;
	int		current_len;
	char	*new_line;
	int		i;

	max_width = find_max_width(map);
	map->cols = max_width;
	y = 0;
	while (y < map->rows)
	{
		current_len = ft_strlen(map->map[y]);
		new_line = ft_calloc(max_width + 1, sizeof(char));
		if (!new_line)
			exit_with_error("Error: Memory allocation failed\n");
		i = 0;
		while (i < current_len)
		{
			if (map->map[y][i] == ' ')
				new_line[i] = 'T';
			else
				new_line[i] = map->map[y][i];
			i++;
		}
		while (i < max_width)
		{
			new_line[i] = 'T';
			i++;
		}
		new_line[max_width] = '\0';
		free(map->map[y]);
		map->map[y] = new_line;
		y++;
	}
}

static int	validate_characters_and_player(t_map *map)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (map->map[y][x])
		{
			if (!is_valid_char(map->map[y][x]) && map->map[y][x] != 'T')
				exit_with_error("Error: Invalid character in map\n");
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S' ||
				map->map[y][x] == 'E' || map->map[y][x] == 'W')
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1)
		exit_with_error("Error: Map must have exactly one player\n");
	return (1);
}

static int	check_borders(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->cols)
	{
		if (map->map[0][x] != '1' && map->map[0][x] != 'T')
			exit_with_error("Error: Map must be surrounded by walls (top)\n");
		if (map->map[map->rows - 1][x] != '1' && map->map[map->rows - 1][x] != 'T')
			exit_with_error("Error: Map must be surrounded by walls (bottom)\n");
		x++;
	}
	y = 0;
	while (y < map->rows)
	{
		if (map->map[y][0] != '1' && map->map[y][0] != 'T')
			exit_with_error("Error: Map must be surrounded by walls (left)\n");
		if (map->map[y][map->cols - 1] != '1' && map->map[y][map->cols - 1] != 'T')
			exit_with_error("Error: Map must be surrounded by walls (right)\n");
		y++;
	}
	return (1);
}

static int	check_walkable_neighbors(t_map *map, int x, int y)
{
	if (x > 0 && map->map[y][x - 1] == 'T')
		return (0);
	if (x < map->cols - 1 && map->map[y][x + 1] == 'T')
		return (0);
	if (y > 0 && map->map[y - 1][x] == 'T')
		return (0);
	if (y < map->rows - 1 && map->map[y + 1][x] == 'T')
		return (0);
	return (1);
}

static int	validate_walls(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (is_walkable(map->map[y][x]))
			{
				if (!check_walkable_neighbors(map, x, y))
				{
					ft_printf("Error: Invalid map at position [%d][%d] = '%c'\n",
							y, x, map->map[y][x]);
					exit_with_error("Error: Walkable area is not properly surrounded by walls\n");
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

void	validate_map(t_map *map)
{
	if (!map || !map->map)
		exit_with_error("Error: Map is NULL\n");
	if (!map->north_texture || !map->south_texture || 
		!map->west_texture || !map->east_texture)
		exit_with_error("Error: Missing texture(s)\n");
	if (!map->floor_color_set || !map->ceiling_color_set)
		exit_with_error("Error: Missing floor or ceiling color\n");
	normalize_map(map);
	validate_characters_and_player(map);
	check_borders(map);
	validate_walls(map);
	ft_printf("✓ Map validation passed!\n");
}