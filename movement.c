#include "cub3d.h"

int	key_press(int key, t_game *game)
{
	if (key == W)
		game->key_w = 1;
	else if (key == S)
		game->key_s = 1;
	else if (key == A)
		game->key_a = 1;
	else if (key == D)
		game->key_d = 1;
	else if (key == LEFT)
		game->key_left = 1;
	else if (key == RIGHT)
		game->key_right = 1;
	else if (key == ESC)
		close_window(game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == W)
		game->key_w = 0;
	else if (key == S)
		game->key_s = 0;
	else if (key == A)
		game->key_a = 0;
	else if (key == D)
		game->key_d = 0;
	else if (key == LEFT)
		game->key_left = 0;
	else if (key == RIGHT)
		game->key_right = 0;
	return (0);
}

int	move_player(t_game *game)
{
	double	new_x;
	double	new_y;
	double	new_angle;
	int		updated;

	new_x = game->player->pos_x;
	new_y = game->player->pos_y;
	new_angle = game->player->angle;
	updated = 0;
	if (game->key_w)
	{
		new_x += cos(game->player->angle) * MOVE_STEP;
		new_y += sin(game->player->angle) * MOVE_STEP;
		updated = 1;
	}
	if (game->key_s)
	{
		new_x -= cos(game->player->angle) * MOVE_STEP;
		new_y -= sin(game->player->angle) * MOVE_STEP;
		updated = 1;
	}
	if (game->key_a)
	{
		new_x -= cos(game->player->angle + PI / 2) * MOVE_STEP;
		new_y -= sin(game->player->angle + PI / 2) * MOVE_STEP;
		updated = 1;
	}
	if (game->key_d)
	{
		new_x += cos(game->player->angle + PI / 2) * MOVE_STEP;
		new_y += sin(game->player->angle + PI / 2) * MOVE_STEP;
		updated = 1;
	}
	if (game->key_right)
	{
		new_angle += ROT_SPEED;
		updated = 1;
	}
	if (game->key_left)
	{
		new_angle -= ROT_SPEED;
		updated = 1;
	}
	if (!updated)
		return (0);
	game->player->pos_x = new_x;
	game->player->pos_y = new_y;
	game->player->angle = new_angle;
	draw_player(game);
	return (0);
}
