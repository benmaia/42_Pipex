/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:36:07 by bmiguel-          #+#    #+#             */
/*   Updated: 2021/12/02 20:43:29 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	n_arg;
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	va_start(n_arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (ft_strchr("cspdiuxX", format[++i]))
			{
				counter += ((int (*)())ft_func_select
						(format[i++]))(va_arg(n_arg, void *));
				continue ;
			}
		}
		write(1, &format[i], 1);
		i++;
		counter++;
	}
	va_end(n_arg);
	return (counter);
}
