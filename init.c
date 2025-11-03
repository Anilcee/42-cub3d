#include "cub3d.h"

static void	init_player(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		exit_with_error("Player allocation failed");
	game->player->pos_x = 0;
	game->player->pos_y = 0;
	game->player->angle = 0;
	game->player->dir_x = 0;
	game->player->dir_y = 0;
	game->player->img = NULL;
}

static void	init_keys(t_game *game)
{
	game->key_w = 0;
	game->key_a = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
}

static void	init_images(t_game *game)
{
	int		img_height;
	int		img_width;
	char	*img_path;

	img_path = "pacman.xpm";
	game->player->img = mlx_xpm_file_to_image(game->mlx, img_path,
			&img_width, &img_height);
	if (!game->player->img)
		exit_with_error("Failed to load player image");
}

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	init_player(game);
	init_keys(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_with_error("Failed to initialize mlx");
	game->size_x = 10 * T_S;
	game->size_y = 10 * T_S;
	game->win = mlx_new_window(game->mlx, game->size_x, game->size_y, "Cub3D");
	if (!game->win)
		exit_with_error("Failed to create window");
	init_images(game);
}
