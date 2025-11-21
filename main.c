#include "cub3d.h"

void	print_config(t_map *map)
{
	ft_printf("=== Config Information ===\n");
	ft_printf("North texture: %s\n", map->north_texture);
	ft_printf("South texture: %s\n", map->south_texture);
	ft_printf("West texture: %s\n", map->west_texture);
	ft_printf("East texture: %s\n", map->east_texture);
	ft_printf("Floor color (RGB): %d\n", map->floor_color);
	ft_printf("Ceiling color (RGB): %d\n", map->ceiling_color);
	ft_printf("Map rows: %d\n", map->rows);
	ft_printf("Map cols: %d\n", map->cols);
	ft_printf("=========================\n");
}

int close_window(t_game *game)
{
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}
void draw_player(t_game *game)
{
	mlx_clear_window(game->mlx,game->win);
	int x = game->player->pos_x;
	int y = game->player->pos_y;
	printf("%d \n", x);
	mlx_put_image_to_window(game->mlx, game->win,game->player->img, x * T_S/8, y * T_S/8);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, ON_KEYPRESS, KEY_PRESS_MASK, key_press, game);
	mlx_hook(game->win, ON_KEYRELEASE, KEY_RELEASE_MASK, key_release, game);
	mlx_loop_hook(game->mlx, move_player, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
}

int main( int argc, char **argv)
{

	if (argc != 2)
		exit_with_error("Usage: ./cub3d <map_file.cub>");
	check_file(argv[1]);
	t_game	game;
	init_game(&game);
	load_map(&game, argv[1]);
	validate_map(game.map);
	find_player_position(&game);
	print_config(game.map);
	draw_player(&game);
	setup_hooks(&game);
	return (0);
}
