#include "cub3d.h"

static void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)game->size_x - 1;
	ray->dir_x = game->player->dir_x + game->player->plane_x * ray->camera_x;
	ray->dir_y = game->player->dir_y + game->player->plane_y * ray->camera_x;
	ray->map_pos_x = (int)game->player->pos_x;
	ray->map_pos_y = (int)game->player->pos_y;
	if (ray->dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}

static void	calculate_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = INFINITY_DIST;
	else
	{
		ray->delta_dist_x = 1.0 / ray->dir_x;
		if (ray->delta_dist_x < 0)
			ray->delta_dist_x = -ray->delta_dist_x;
	}
	if (ray->dir_y == 0)
		ray->delta_dist_y = INFINITY_DIST;
	else
	{
		ray->delta_dist_y = 1.0 / ray->dir_y;
		if (ray->delta_dist_y < 0)
			ray->delta_dist_y = -ray->delta_dist_y;
	}
}

static void	calculate_side_dist(t_ray *ray, t_game *game)
{
	if (ray->step_x < 0)
		ray->side_dist_x = (game->player->pos_x - ray->map_pos_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_pos_x + 1.0 - game->player->pos_x) * ray->delta_dist_x;
	if (ray->step_y < 0)
		ray->side_dist_y = (game->player->pos_y - ray->map_pos_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_pos_y + 1.0 - game->player->pos_y) * ray->delta_dist_y;
}

static void	dda_loop(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_pos_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_pos_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map->map[ray->map_pos_y][ray->map_pos_x] == '1')
			ray->hit = 1;
	}
}

void	cast_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < game->size_x)
	{
		init_ray(&ray, game, x);
		calculate_delta_dist(&ray);
		calculate_side_dist(&ray, game);
		dda_loop(&ray, game);
		x++;
	}
}
