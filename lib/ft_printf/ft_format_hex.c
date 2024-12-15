/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:41:26 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:54:56 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	bit_size_nbr(register unsigned long nbr)
{
	register unsigned long	nbit;

	nbit = sizeof(nbr) * CHAR_BIT - __builtin_clz(nbr);
	if ((__builtin_clz(nbr) % 4) > 0)
		nbit += (__builtin_clz(nbr) % 4);
	return (nbit);
}

static char	*ft_calc_base_hex(char *str, register size_t nbr)
{
	char			*wtab;
	register int	mod;
	register size_t	i;

	wtab = "0123456789abcdef";
	i = 0;
	if (nbr != 0)
	{
		while (nbr != 0)
		{
			mod = nbr % 16;
			nbr = nbr / 16 ;
			str[i] = wtab[mod];
			i++;
		}
	}
	else
	{
		str[0] = '0';
		i++;
	}
	str[i] = '\0';
	ft_rev_char_tab(str, i);
	return (str);
}

static t_print	ft_hex(register size_t num, t_print t_str)
{
	if (t_str.sharp == TRUE && num != 0)
	{
		if (t_str.t_spc == 'x')
			t_str = ft_buffer(t_str, "0x");
		else
			t_str = ft_buffer(t_str, "0X");
		if (t_str.ks_ctrl_err == TRUE)
			return (t_str);
		t_str.sharp = FALSE;
	}
	t_str.str_num = ft_calc_base_hex(t_str.str_num, num);
	if (t_str.t_spc == 'X')
		t_str.str_num = ft_upcase_str(t_str.str_num);
	t_str = ft_buffer(t_str, t_str.str_num);
	return (t_str);
}

t_print	ft_format_hex(register unsigned long num, t_print t_str)
{
	if (t_str.sharp == TRUE && t_str.dot == TRUE)
		t_str.ks_ctrl_err = TRUE;
	else
	{
		t_str.len_s = (bit_size_nbr(num) >> 2);
		t_str.str_num = ft_calloc (t_str.len_s + 1, sizeof (char));
		if (t_str.str_num == NULL)
		{	
			t_str.ks_ctrl_err = TRUE;
			return (t_str);
		}
		if (t_str.dot == TRUE)
		{
			t_str = ft_fill_zero(t_str);
		}
		t_str = ft_hex(num, t_str);
		free(t_str.str_num);
	}
	return (t_str);
}
