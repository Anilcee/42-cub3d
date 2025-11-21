#include "cub3d.h"

void cast_rays(t_game *game)
{
	int x;
	double cameraX;
	double rayDirX;
	double rayDirY;

	x = 0;
	while (x < game->size_y)
    {
      cameraX = 2 * x / (double)game->size_y - 1;
      rayDirX = game->player->dir_x + game->player->plane_x * cameraX;
      rayDirY = game->player->dir_y + game->player->plane_y * cameraX;
	  x++;
	}
}
