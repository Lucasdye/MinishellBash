/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 10:25:15 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 16:41:44 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print	ft_fill_zero(t_print t_str)
{
	register size_t	i;

	i = 0;
	t_str.str_tmp[0] = '0';
	t_str.str_tmp[1] = '\0';
	while (i < (t_str.nbr_prec - t_str.len_s))
	{
		t_str = ft_buffer(t_str, t_str.str_tmp);
		if (t_str.ks_ctrl_err == TRUE)
			return (t_str);
	}
	return (t_str);
}

t_print	ft_padding(t_print str, char kssg)
{
	char			*str_padd;
	register size_t	i;

	if (((ssize_t)str.nbr_padd - (ssize_t)str.len_s - kssg) >= 0)
	{
		str_padd = malloc(sizeof(char) * (str.nbr_padd - str.len_s - kssg) + 1);
		if (str_padd == NULL)
			str.ks_ctrl_err = TRUE;
		else
		{
			i = 0;
			if (str.nbr_padd > str.len_s)
			{
				while (i < (str.nbr_padd - str.len_s - kssg))
				{
					str_padd[i] = str.char_padd;
					i++;
				}
				str_padd[i] = '\0';
				str = ft_buffer(str, str_padd);
			}
			free(str_padd);
		}
	}
	return (str);
}

t_print	ft_flag_check_minus(t_print str)
{
	if (((str.minus == TRUE) || (str.zero == TRUE)) && (str.ks_padd == FALSE))
		str.ks_padd = TRUE;
	if (str.ks_padd == TRUE)
	{
		if (ft_isdigit(str.t_spc))
		{
			str.nbr_padd = (str.nbr_padd * 10) + (str.t_spc - 48);
		}
		else
		{
			str.minus = FALSE;
			str.ks_ctrl_flow = FALSE;
			str.ks_padd = FALSE;
		}
	}
	return (str);
}

t_print	ft_flag_check(t_print str)
{
	if (str.zero == TRUE)
	{
		if (str.minus == FALSE)
			str.char_padd = '0';
		else
			str.char_padd = '\x20';
		str = ft_flag_check_minus(str);
	}	
	else if (str.space == TRUE)
		str.char_padd = '\x20';
	return (str);
}
