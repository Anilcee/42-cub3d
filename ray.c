#include "cub3d.h"

void cast_rays(t_game *game)
{
	int x;

	x = 0;
	while (x < game->size_x)
    {
	  t_ray ray;
      ray.camera_x = 2 * x / (double)game->size_x - 1;
      ray.dir_x = game->player->dir_x + game->player->plane_x * ray.camera_x;
      ray.dir_y = game->player->dir_y + game->player->plane_y * ray.camera_x;
	  ray.map_pos_x = (int)game->player->pos_x;
	  ray.map_pos_y = (int)game->player->pos_y;
	  if(ray.dir_x < 0)
		ray.step_x = -1;
	  else
		ray.step_x = 1;
	  if(ray.dir_y < 0)
		ray.step_y = -1;
	  else
		ray.step_y = 1;
	  
	  x++;
	}
}
