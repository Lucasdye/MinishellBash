/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fac_func_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:54:23 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:58:31 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//t_print	ft_fac_format_c(va_arg(str.arg, void *), t_print str)
t_print	ft_fac_format_c(t_print str)
{
	t_print	t_str;

	t_str = ft_format_c(va_arg(str.arg, int), str);
	return (t_str);
}

t_print	ft_fac_format_str(t_print str)
{
	t_print	t_str;

	if ((str.space == TRUE))
	{
		str.space = FALSE;
		str.ks_ctrl_err = TRUE;
		return (str);
	}
	t_str = ft_format_str(va_arg(str.arg, char *), str);
	return (t_str);
}

t_print	ft_fac_format_prt(t_print str)
{
	t_print	t_str;

	t_str = ft_format_hex_ptr((unsigned long long )va_arg(str.arg, void *),
			str);
	return (t_str);
}

t_print	ft_fac_format_dint(t_print str)
{
	t_print	t_str;

	t_str = ft_format_int(va_arg(str.arg, int), str);
	return (t_str);
}

t_print	ft_fac_format_int(t_print str)
{
	t_print	t_str;

	t_str = ft_format_int(va_arg(str.arg, int), str);
	return (t_str);
}
