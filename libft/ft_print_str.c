/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancengiz <ancengiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:30:11 by ancengiz          #+#    #+#             */
/*   Updated: 2025/03/01 17:30:12 by ancengiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *c)
{
	int	count;
	int	i;

	if (!c)
		return (ft_print_str("(null)"));
	i = 0;
	count = 0;
	while (c[i])
	{
		count += ft_print_char(c[i]);
		i++;
	}
	return (count);
}
