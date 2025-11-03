#include "cub3d.h"

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

void	init_images(t_game *game)
{
	int img_height;
	int img_width;
	char *img="pacman.xpm";

	game->player->img= mlx_xpm_file_to_image(game->mlx,img,&img_width,&img_height);

}


int main( int argc, char **argv)
{

	if (argc != 2)
		exit_with_error("Usage: ./cub3d <map_file.cub>");
	check_file_extension(argv[1]);
	t_game	game;
	game.player = malloc(sizeof(t_player));
	game.mlx = mlx_init();
	game.size_x = 10 * T_S;
	game.size_y = 10 * T_S;
	game.win = mlx_new_window(game.mlx, game.size_x, game.size_y, "Cub3D");
	init_images(&game);
	draw_player(&game);
	mlx_key_hook(game.win, move_player,&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
