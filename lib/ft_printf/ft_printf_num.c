/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:31:55 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 16:39:39 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_size(int nbr)
{
	register size_t	size;

	size = 0;
	if (nbr < 0)
		nbr = -nbr;
	else if (nbr == 0)
	{
		size++;
		return (size);
	}
	while (nbr > 0)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

static void	ft_calc_base_10(char *str, register int len_s, register int nbr)
{
	int				mod;
	register int	i;

	i = 1;
	if (nbr < 0)
		nbr = ft_abs(nbr);
	while (nbr != 0)
	{
		mod = nbr % 10;
		nbr = nbr / 10 ;
		str[len_s - i] = mod + 48;
		i++;
	}
	str[len_s] = '\0';
}

static void	ft_itoa_i(t_print *t_str, register int num)
{
	t_str->len_s = ft_get_size(num);
	t_str->str_num = ft_calloc (t_str->len_s + 1, sizeof (char));
	if (t_str->str_num == NULL)
	{
		t_str->ks_ctrl_err = TRUE;
		return ;
	}
	if (num == 0)
	{
		t_str->str_num[0] = '0';
		t_str->str_num[1] = '\0';
	}
	else if (num == -2147483648)
	{
		free(t_str->str_num);
		t_str->str_num = ft_strdup("2147483648");
		return ;
	}
	else
		ft_calc_base_10(t_str->str_num, t_str->len_s, num);
	return ;
}

static t_print	ft_flag__int(register int num, t_print t_str)
{
	if ((t_str.plus == TRUE) && (num >= 0))
	{
		t_str.plus = FALSE;
		t_str.ks_ctrl_flow = FALSE;
		t_str = ft_buffer(t_str, "+");
	}
	else if ((t_str.space == TRUE) && (num >= 0))
	{
		t_str.space = FALSE;
		t_str.ks_ctrl_flow = FALSE;
		t_str = ft_buffer_c(t_str, t_str.char_padd);
	}
	ft_itoa_i(&t_str, num);
	return (t_str);
}

t_print	ft_format_int(register int num, t_print t_str)
{
	char	ks_sign;

	ks_sign = FALSE;
	if (t_str.t_spc == 'u')
		t_str = ft_flag_uint(num, t_str);
	else
	{
		t_str = ft_flag__int(num, t_str);
		if (t_str.ks_ctrl_err == TRUE)
			return (t_str);
		if (num < 0)
		{
			ks_sign = TRUE;
			t_str = ft_buffer(t_str, "-");
		}
		if (t_str.zero == TRUE)
		{
			t_str.zero = FALSE;
			t_str.ks_ctrl_flow = FALSE;
			t_str = ft_padding(t_str, ks_sign);
		}
		t_str = ft_buffer(t_str, t_str.str_num);
		free(t_str.str_num);
	}
	return (t_str);
}
