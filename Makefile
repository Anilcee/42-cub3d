CC = cc
#CFLAGS = -Wall -Wextra -Werror

# Dosya yolları
SRCS = main.c ray.c map_validation.c movement.c init.c
OBJS = $(SRCS:.c=.o)
NAME = cub3d

MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
LINUX_LIBS = -lXext -lX11 -lm

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft $(LINUX_LIBS) 

$(MLX_LIB):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) fclean

re: fclean all
