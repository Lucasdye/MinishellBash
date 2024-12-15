/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fac_func_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:01:16 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:58:47 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print	ft_fac_format_uint(t_print str)
{
	t_print	t_str;

	if ((str.plus == TRUE))
	{
		str.plus = FALSE;
		str.ks_ctrl_err = TRUE;
		return (str);
	}
	t_str = ft_format_int(va_arg(str.arg, int), str);
	return (t_str);
}

t_print	ft_fac_format_xhex(t_print str)
{
	t_print	t_str;

	t_str = ft_format_hex(va_arg(str.arg, unsigned int), str);
	return (t_str);
}

t_print	ft_fac_format_mxhex(t_print str)
{
	t_print	t_str;

	t_str = ft_format_hex(va_arg(str.arg, unsigned int), str);
	return (t_str);
}

t_print	ft_fac_format_perc(t_print str)
{
	t_print	t_str;

	t_str = ft_format_c(('%'), str);
	return (t_str);
}
