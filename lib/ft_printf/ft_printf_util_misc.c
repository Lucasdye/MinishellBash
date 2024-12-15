/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util_misc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 07:58:32 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 16:42:06 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_print	ft_dim_buffer(t_print str, register size_t size_data)
{
	char			*str_tmp;
	register int	redim;

	redim = FALSE;
	while ((str.size_buff - str.idx_buff) <= size_data)
	{
		str.size_buff *= 2;
		redim = TRUE;
	}
	if (redim == TRUE)
	{
		str_tmp = ft_strdup(str.str_buff);
		free(str.str_buff);
		str.str_buff = ft_calloc(str.size_buff, sizeof(char));
		if (str.str_buff == NULL)
			str.ks_ctrl_err = TRUE;
		else
			ft_strcat(str.str_buff, str_tmp);
		free(str_tmp);
	}
	return (str);
}

t_print	ft_buffer(t_print t_str, char *add_str)
{
	register size_t	i;

	t_str.len_s = ft_strlen(add_str);
	t_str = ft_dim_buffer(t_str, t_str.len_s);
	if (t_str.ks_ctrl_err == TRUE)
		return (t_str);
	i = 0;
	while (i < t_str.len_s)
	{
		t_str.str_buff[t_str.idx_buff + i] = add_str[i];
		i++;
	}
	t_str.idx_buff += i;
	return (t_str);
}

t_print	ft_buffer_c(t_print t_str, char add_c)
{
	register size_t	i;

	t_str.len_s = 1;
	t_str = ft_dim_buffer(t_str, t_str.len_s);
	if (t_str.ks_ctrl_err == TRUE)
		return (t_str);
	i = 0;
	while (i < t_str.len_s)
	{
		t_str.str_buff[t_str.idx_buff + i] = add_c;
		i++;
	}
	t_str.idx_buff += i;
	return (t_str);
}
