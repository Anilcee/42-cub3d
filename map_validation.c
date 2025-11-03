#include "cub3d.h"

void	exit_with_error(char *msg)
{
	perror (msg);
	exit (1);
}

void	check_file_extension(char *file_path)
{
	file_path = file_path + ft_strlen(file_path) - 4;
	if (ft_strncmp(file_path, ".cub", 4) != 0)
	{
		ft_printf("Error: Invalid file extension must be .cub");
		exit(EXIT_FAILURE);
	}
}

int	open_file(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error opening file");
	return (fd);
}