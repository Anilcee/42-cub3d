#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100

# define ON_KEYPRESS 2
# define ON_KEYRELEASE 3
# define KEY_PRESS_MASK (1L << 0)
# define KEY_RELEASE_MASK (1L << 1)

#define ROT_SPEED 0.1
# define MOVE_SPEED 1.0
# define T_S 64
# define FOV 60
# define NUM_RAYS 1200
# define WALL_STRIP_WIDTH (NUM_RAYS / FOV)
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define TEX_NUM 4
# define MOVE_STEP 0.05
# define ROTATE_ANGLE 5
# define PI 3.14159265358979323846

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	angle;
	double	dir_x;
	double	dir_y;
	void * img;
}				t_player;

typedef struct s_map
{
	char	**map;
	int		rows;
	int		cols;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color;
	int		ceiling_color;
	int		floor_color_set;
	int		ceiling_color_set;
}				t_map;

typedef struct s_map_line
{
	char *line;
	struct s_map_line *next;
} t_map_line;

typedef struct s_map_builder
{
	t_map_line	*head;
	t_map_line	*tail;
	int			rows;
	int			max_cols;
}				t_map_builder;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		textures[TEX_NUM];
	t_player	*player;
	t_map		*map;
	int			size_x;
	int			size_y;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
}				t_game;

void	exit_with_error(char *msg);
void	check_file(char *file_path);
int		open_file(const char *file_path);
void	load_map(t_game *game, const char *file_path);
void	validate_map(t_map *map);
int		move_player(t_game *game);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
int		close_window(t_game *game);
void	draw_player(t_game *game);
void	init_game(t_game *game);
void	find_player_position(t_game *game);

#endif
