/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:57:10 by jveuille          #+#    #+#             */
/*   Updated: 2023/05/06 16:30:31 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print	ft_format_c(char str, t_print t_str)
{
	t_str = ft_buffer_c(t_str, str);
	return (t_str);
}

t_print	ft_format_str(char *str, t_print t_str)
{
	if (str == NULL)
		t_str = ft_buffer(t_str, "(null)");
	else
		t_str = ft_buffer(t_str, str);
	return (t_str);
}

t_print	fill_str_to_char(t_print t_str, char format)
{
	t_str.str_tmp[0] = format;
	t_str.str_tmp[1] = '\0';
	t_str = ft_buffer(t_str, t_str.str_tmp);
	return (t_str);
}
