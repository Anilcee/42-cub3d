#include "cub3d.h"

static int	parse_rgb(const char *str)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	r = ft_atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	g = ft_atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	b = ft_atoi(&str[i]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_with_error("Error: Invalid RGB values (must be 0-255)\n");
	return ((r << 16) | (g << 8) | b);
}

static char	*parse_texture_path(const char *line)
{
	int		i;
	int		start;
	char	*path;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	path = ft_calloc(i - start + 1, sizeof(char));
	if (!path)
		exit_with_error("Error: Failed to allocate texture path\n");
	ft_strlcpy(path, &line[start], i - start + 1);
	return (path);
}

static void	parse_config_textures(t_map *map, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (map->north_texture)
			exit_with_error("Error: Duplicate NO entry in .cub file\n");
		map->north_texture = parse_texture_path(line + 3);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (map->south_texture)
			exit_with_error("Error: Duplicate SO entry in .cub file\n");
		map->south_texture = parse_texture_path(line + 3);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (map->west_texture)
			exit_with_error("Error: Duplicate WE entry in .cub file\n");
		map->west_texture = parse_texture_path(line + 3);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (map->east_texture)
			exit_with_error("Error: Duplicate EA entry in .cub file\n");
		map->east_texture = parse_texture_path(line + 3);
	}
}
static void	parse_config_colors(t_map *map, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (map->floor_color_set)
			exit_with_error("Error: Duplicate F entry in .cub file\n");
		map->floor_color = parse_rgb(line + 2);
		map->floor_color_set = 1;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (map->ceiling_color_set)
			exit_with_error("Error: Duplicate C entry in .cub file\n");
		map->ceiling_color = parse_rgb(line + 2);
		map->ceiling_color_set = 1;
	}
}

static int	is_config_line(const char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "NO ", 3) == 0 || 
		ft_strncmp(&line[i], "SO ", 3) == 0 ||
		ft_strncmp(&line[i], "WE ", 3) == 0 || 
		ft_strncmp(&line[i], "EA ", 3) == 0 ||
		ft_strncmp(&line[i], "F ", 2) == 0 || 
		ft_strncmp(&line[i], "C ", 2) == 0)
		return (1);
	return (0);
}

static int is_whitespace_only(const char *line)
{
	int i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int is_map_start(const char *line)
{
	int i;
	int j;

	if (!line)
		return (0);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	j = i;
	while (line[j])
	{
		if (!ft_strchr("01NSEW \t\n", line[j]))
			return (0);
		j++;
	}
	return (1);
}

static char *strip_newline(char *line)
{
	size_t len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static void append_line(t_map_line **head, t_map_line **tail,
						char *line, int *rows, int *max_cols)
{
	t_map_line *node;
	int len;

	node = ft_calloc(1, sizeof(t_map_line));
	if (!node)
		exit_with_error("Failed to allocate map node\n");
	node->line = line;
	if (*tail)
		(*tail)->next = node;
	else
		*head = node;
	*tail = node;
	len = ft_strlen(line);
	if (len > *max_cols)
		*max_cols = len;
	(*rows)++;
}

static char **list_to_array(t_map_line *head, int rows)
{
	char **matrix;
	int i;
	t_map_line *tmp;

	matrix = ft_calloc(rows + 1, sizeof(char *));
	if (!matrix)
		exit_with_error("Failed to allocate map matrix\n");
	i = 0;
	while (head)
	{
		matrix[i++] = head->line;
		tmp = head;
		head = head->next;
		free(tmp);
	}
	matrix[i] = NULL;
	return (matrix);
}

static void set_player_orientation(t_game *game, char c)
{
	if (c == 'N')
		game->player->angle = -PI / 2;
	else if (c == 'S')
		game->player->angle = PI / 2;
	else if (c == 'E')
		game->player->angle = 0;
	else if (c == 'W')
		game->player->angle = PI;
	game->player->dir_x = cos(game->player->angle);
	game->player->dir_y = sin(game->player->angle);
}

static int is_player_char(char c)
{
	return (c == 'W' || c == 'N' || c == 'E' || c == 'S');
}

void find_player_position(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->cols)
		{
			if (is_player_char(game->map->map[y][x]))
			{
				set_player_orientation(game, game->map->map[y][x]);
				game->player->pos_x = x + 0.5;
				game->player->pos_y = y + 0.5;
				return;
			}
			x++;
		}
		y++;
	}
}

static int	handle_pre_map_line(t_game *game, char *line)
{
	if (is_config_line(line))
	{
		parse_config_textures(game->map, line);
		parse_config_colors(game->map, line);
		free(line);
		return (1);
	}
	if (is_whitespace_only(line))
	{
		free(line);
		return (1);
	}
	if (!is_map_start(line))
	{
		free(line);
		return (1);
	}
	return (0);
}

static void	read_map_data(int fd, t_game *game, t_map_builder *builder)
{
	char	*line;
	int		started;

	started = 0;
	while ((line = get_next_line(fd)))
	{
		if (!started && handle_pre_map_line(game, line))
			continue;
		if (!started)
			started = 1;
		if (is_whitespace_only(line))
		{
			free(line);
			continue;
		}
		append_line(&builder->head, &builder->tail, strip_newline(line),
			&builder->rows, &builder->max_cols);
	}
}

void	load_map(t_game *game, const char *file_path)
{
	int			fd;
	t_map_builder	builder;

	fd = open_file(file_path);
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		exit_with_error("Failed to allocate map struct\n");
	builder.head = NULL;
	builder.tail = NULL;
	builder.rows = 0;
	builder.max_cols = 0;
	read_map_data(fd, game, &builder);
	close(fd);
	if (builder.rows == 0)
		exit_with_error("Map data not found in .cub file\n");
	game->map->map = list_to_array(builder.head, builder.rows);
	game->map->rows = builder.rows;
}
