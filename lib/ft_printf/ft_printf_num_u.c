/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:10:43 by jveuille          #+#    #+#             */
/*   Updated: 2023/05/06 16:31:01 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_size(register unsigned int nbr)
{
	size_t	size;

	size = 0;
	if (nbr == 0)
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

static char	*ft_calc_base_10(char *str, register int len_s,
	register unsigned int nbr)
{
	register int	mod;
	register int	i;

	i = 0;
	while (nbr != 0)
	{
		mod = nbr % 10;
		nbr = nbr / 10 ;
		str[len_s - i - 1] = mod + 48;
		i++;
	}
	return (str);
}

static char	*ft_uitoa(register unsigned int num, t_print *t_str)
{
	char	*str_num;

	t_str->len_s = ft_get_size(num);
	str_num = ft_calloc (t_str->len_s + 1, sizeof (char));
	if (str_num == NULL)
		return (NULL);
	if (num == 0)
		str_num[0] = '0';
	else
		str_num = ft_calc_base_10(str_num, t_str->len_s, num);
	str_num[t_str->len_s] = '\0';
	return (str_num);
}

t_print	ft_flag_uint(register unsigned int num, t_print t_str)
{
	t_str.str_num = ft_uitoa((unsigned int)(num), &t_str);
	if (t_str.space == TRUE)
	{
		t_str.str_tmp[0] = '\x20';
		t_str.str_tmp[1] = '\0';
		t_str.ks_ctrl_flow = TRUE;
		t_str.space = FALSE;
	}
	if (t_str.zero == TRUE)
	{
		t_str.zero = FALSE;
		t_str.ks_ctrl_flow = FALSE;
		t_str = ft_padding(t_str, FALSE);
	}
	if (t_str.ks_ctrl_flow == TRUE)
	{
		t_str = ft_buffer(t_str, t_str.str_tmp);
			t_str.ks_ctrl_flow = FALSE;
		if (t_str.ks_ctrl_err == TRUE)
			return (t_str);
	}
	t_str = ft_buffer(t_str, t_str.str_num);
	free(t_str.str_num);
	return (t_str);
}
