#include "cub3d.h"
#include "libft/libft.h"
#include <unistd.h>

void	exit_with_error(char *msg)
{
	write(2,msg,ft_strlen(msg));
	exit (1);
}

void	check_file(char *file)
{
	char *file_path;
	file_path = file + ft_strlen(file) - 4;
	if (ft_strncmp(file_path, ".cub", 4) != 0)
	{
		ft_printf("Error: Invalid file extension must be .cub \n");
		exit(EXIT_FAILURE);
	}
	open_file(file);
}
int	open_file(const char *file_path)
{
	int	fd;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error opening file\n");
	return (fd);
}