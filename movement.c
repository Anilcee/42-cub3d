#include "cub3d.h"

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