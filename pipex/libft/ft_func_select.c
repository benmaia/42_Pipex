/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:46:23 by bmiguel-          #+#    #+#             */
/*   Updated: 2021/12/02 20:45:29 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_func_select(char c)
{
	if (c == 'c')
		return (ft_printf_c);
	else if (c == 's')
		return (ft_printf_s);
	else if (c == 'p')
		return (ft_printf_p);
	else if (c == 'd')
		return (ft_printf_d);
	else if (c == 'i')
		return (ft_printf_d);
	else if (c == 'u')
		return (ft_printf_u);
	else if (c == 'x')
		return (ft_printf_x);
	else
		return (ft_printf_xx);
}
