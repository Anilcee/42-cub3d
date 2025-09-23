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

int	move_player(int key, t_game *game)
{
	double	new_x;
	double	new_y;
	double	new_angle;

	new_x = game->player->pos_x;
	new_y = game->player->pos_y;
	new_angle = game->player->angle;
	
	if (key == S)
	{
		new_x -= cos(game->player->angle);
		new_y -= sin(game->player->angle);
	}
	else if (key == A)
	{
		new_x -= cos(game->player->angle + PI/2);
		new_y -= sin(game->player->angle + PI/2);
	}
	else if (key == W)
	{
		new_x += cos(game->player->angle);
		new_y += sin(game->player->angle);
	}
	else if (key == D)
	{
		new_x += cos(game->player->angle + PI/2);
		new_y += sin(game->player->angle + PI/2);
	}
	else if (key == RIGHT)
		new_angle += 0.1;
	else if (key == LEFT)
		new_angle -= 0.1;
	else if (key == ESC)
		close_window(game);
	else
		return (0);
		
	game->player->pos_x = new_x;
	game->player->pos_y = new_y;
	game->player->angle = new_angle;
	draw_player(game);
	return (0);
}
void	init_images(t_game *game)
{
	int img_height;
	int img_width;
	char *img="pacman.xpm";

	game->player->img= mlx_xpm_file_to_image(game->mlx,img,&img_width,&img_height);

}


int main()
{
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
