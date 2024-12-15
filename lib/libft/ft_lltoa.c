/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 09:36:57 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/12 15:27:30 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(register t_lssize_t nbr)
{
	register size_t	size;

	size = 0;
	if (nbr < 0)
		size++;
	else if (nbr == 0)
	{
		size++;
		return (size);
	}
	while (nbr != 0)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

static void	ft_calc_base_10(t_str *dt, register t_lssize_t nbr)
{
	register int	mod;

	while (nbr != 0)
	{
		mod = nbr % 10;
		nbr = nbr / 10 ;
		dt->str[dt->size - dt->idx - 1] = mod + 48;
		dt->idx++;
	}
	dt->str[dt->size] = '\0';
	return ;
}

char	*ft_lltoa( t_lssize_t n)
{
	t_str	dt;

	dt.size = ft_get_size(n);
	dt.str = ft_calloc (dt.size + 1, sizeof (char));
	if (dt.str == NULL)
		return (NULL);
	if (n == 0)
		dt.str[0] = '0';
	else if ((t_lsize_t)n == 9223372036854775808UL)
		return (ft_memcpy(dt.str, "-9223372036854775808", dt.size + 1));
	else
	{
		dt.idx = 0;
		if (n < 0)
		{
			dt.str[0] = '-';
			n = -n;
		}
		ft_calc_base_10(&dt, n);
	}
	return (dt.str);
}
