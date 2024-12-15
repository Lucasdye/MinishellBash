/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hex_ptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:01:01 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:56:20 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	bit_size_lnbr(register unsigned long nbr)
{
	register size_t	nbit;

	nbit = sizeof(nbr) * CHAR_BIT - __builtin_clzl(nbr);
	if ((__builtin_clzl(nbr) % 4) > 0)
		nbit += (__builtin_clzl(nbr) % 4);
	return (nbit);
}

static char	ft_hex_base(int idx)
{
	char	*wtab;

	wtab = "0123456789abcdef";
	return (wtab[idx]);
}

static char	*ft_calc_base_hex_ptr(char *str, register unsigned long int nbr
	, register int nbit)
{
	register unsigned long int	bs_msq;
	register unsigned long int	msq;
	register int				n;
	register int				i;

	bs_msq = 0xf;
	msq = bs_msq << (nbit - 4);
	n = nbit >> 2;
	i = n;
	str[n] = '\0';
	while ((i - 1) >= 0)
	{
		str[n - i] = ft_hex_base((nbr & msq) >> (4 * (i - 1)));
		msq = msq >> 4;
		i--;
	}
	return (str);
}

static t_print	ft_hex(register unsigned long int num, t_print t_str, int nbit)
{
	t_str = ft_buffer(t_str, "0x");
	if (t_str.ks_ctrl_err == TRUE)
		return (t_str);
	t_str.sharp = FALSE;
	t_str.str_num = ft_calc_base_hex_ptr(t_str.str_num, num, nbit);
	if (t_str.t_spc == 'X')
		t_str.str_num = ft_upcase_str(t_str.str_num);
	t_str = ft_buffer(t_str, t_str.str_num);
	return (t_str);
}

t_print	ft_format_hex_ptr(register unsigned long int num, t_print t_str)
{
	register int	nbit;

	if (t_str.sharp == TRUE && t_str.dot == TRUE)
		t_str.ks_ctrl_err = TRUE;
	else if (!num)
		t_str = ft_buffer(t_str, "(nil)");
	else
	{
		nbit = bit_size_lnbr(num);
		t_str.str_num = ft_calloc (((nbit >> 2) + 1), sizeof (char));
		if (t_str.str_num == NULL)
		{	
			t_str.ks_ctrl_err = TRUE;
			return (t_str);
		}
		if (t_str.dot == TRUE)
		{
			t_str = ft_fill_zero(t_str);
		}
		t_str = ft_hex(num, t_str, nbit);
		free(t_str.str_num);
	}
	return (t_str);
}
