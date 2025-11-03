/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancengiz <ancengiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:31:44 by ancengiz          #+#    #+#             */
/*   Updated: 2025/03/01 17:31:45 by ancengiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_type(const char a, va_list args)
{
	int	count;

	count = 0;
	if ((a) == 'c')
		count += ft_print_char(va_arg(args, int));
	if ((a) == 'd' || (a) == 'i')
		count += ft_print_nbr(va_arg(args, int));
	if ((a) == 's')
		count += ft_print_str(va_arg(args, char *));
	if ((a) == 'p')
		count += ft_print_hex(va_arg(args, void *));
	if ((a) == '%')
		count += ft_print_char('%');
	if ((a) == 'u')
		count += ft_print_unsigned_nbr(va_arg(args, unsigned int));
	if ((a) == 'x')
		count += ft_print_x(va_arg(args, unsigned int), 'x');
	if (a == 'X')
		count += ft_print_x(va_arg(args, unsigned int), 'X');
	return (count);
}

int	ft_printf(const char *a, ...)
{
	int		i;
	int		count;
	va_list	args;

	va_start(args, a);
	count = 0;
	i = 0;
	while (a[i])
	{
		if (a[i] == '%')
		{
			i++;
			count += check_type(a[i], args);
		}
		else
			count += ft_print_char(a[i]);
		i++;
	}
	return (count);
}
