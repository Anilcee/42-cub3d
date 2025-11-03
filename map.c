#include "cub3d.h"

static void	set_player_orientation(t_game *game, char c)
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

void	find_player_position(t_game *game)
{
    int	x;
    int	y;

    x = 0;
    y = 0;
    while (y < game->map->rows)
    {
        x = 0;
        while (x < game->map->cols)
        {
            if (game->map->map[y][x] == 'W' ||game->map->map[y][x] == 'N'||
                game->map->map[y][x] == 'E' || game->map->map[y][x] == 'S' )
            {
                set_player_orientation(game, game->map->map[y][x]);
                game->player->pos_x = x + 0.5;
                game->player->pos_y = y + 0.5;
                return ;
            }
            x++;
        }
        y++;
    }
}
