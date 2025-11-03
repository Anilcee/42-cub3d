/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancengiz <ancengiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:22:00 by ancengiz          #+#    #+#             */
/*   Updated: 2025/01/13 01:52:37 by ancengiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(char const *s, char sep)
{
	int	index;
	int	counter;

	index = 0;
	counter = 0;
	while (s[index])
	{
		while (s[index] == sep)
			index++;
		if (s[index])
		{
			counter++;
			while (s[index] != sep && s[index])
				index++;
		}
	}
	return (counter);
}

static size_t	get_word_len(char const *s, char sep)
{
	if (ft_strchr(s, sep) == NULL)
		return (ft_strlen(s));
	return (ft_strchr(s, sep) - s);
}

static void	free_split(char **list)
{
	int	index;

	index = 0;
	while (list[index])
	{
		free(list[index]);
		index++;
	}
	free(list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	int		index;

	index = 0;
	list = (char **)malloc((word_counter(s, c) + 1) * sizeof(char *));
	if (!s || !list)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			list[index] = ft_substr(s, 0, get_word_len(s, c));
			if (!list[index])
			{
				free_split(list);
				return (NULL);
			}
			index++;
		}
		s += get_word_len(s, c);
	}
	list[index] = NULL;
	return (list);
}
