/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:11:21 by jveuille          #+#    #+#             */
/*   Updated: 2023/08/29 09:57:57 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline static int	ft_abs(int nbr)
{
	if (nbr < 0)
		nbr = -nbr;
	return (nbr);
}

static int	ft_get_size(register int nbr)
{
	register size_t	size;

	size = 0;
	if (nbr < 0)
	{
		size++;
		nbr = ft_abs(nbr);
	}
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

static char	*ft_calc_base_10(char *str, register int len_s
	, register int nbr, register int i)
{
	register int	mod;

	nbr = ft_abs(nbr);
	while (nbr != 0)
	{
		mod = nbr % 10;
		nbr = nbr / 10 ;
		str[len_s - i] = mod + 48;
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str_num;
	register int	len_s;
	register int	i;

	len_s = ft_get_size(n);
	str_num = ft_calloc (len_s + 1, sizeof (char));
	if (str_num == NULL)
		return (NULL);
	if (n == 0)
		str_num[0] = '0';
	else if (n == -2147483648)
	{
		free(str_num);
		return (ft_strdup("-2147483648"));
	}
	else
	{
		i = 1;
		if (n < 0)
			str_num[0] = '-';
		ft_calc_base_10(str_num, len_s, n, i);
	}
	str_num[len_s] = '\0';
	return (str_num);
}
