/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancengiz <ancengiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 01:54:41 by ancengiz          #+#    #+#             */
/*   Updated: 2024/12/14 01:54:41 by ancengiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_line(char *buffer)
{
	char	*end_of_line;
	char	*line;

	end_of_line = ft_strchr(buffer, '\n');
	if (!end_of_line)
		end_of_line = buffer + ft_strlen(buffer);
	line = ft_substr(buffer, 0, end_of_line - buffer + 1);
	return (line);
}

static char	*ft_trim_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i] || !buffer[i + 1])
	{
		free(buffer);
		return (NULL);
	}
	result = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i));
	if (!result)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		result[j++] = buffer[i++];
	result[j] = '\0';
	free(buffer);
	return (result);
}

static char	*read_from_file(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (!buffer || !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(temp);
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp);
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_from_file(fd, buffer);
	if (!buffer || !*buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_get_line(buffer);
	buffer = ft_trim_buffer(buffer);
	return (line);
}
