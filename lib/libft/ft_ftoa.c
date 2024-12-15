/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:23:34 by jveuille          #+#    #+#             */
/*   Updated: 2023/09/09 14:28:38 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(int register nbr)
{
	register size_t	size;

	size = 0;
	if (nbr < 0)
	{
		size++;
		nbr = -nbr;
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

static void	null_str(t_str *dt, int p)
{
	register int	i;

	i = 0;
	dt->str[0] = '0';
	if (p != 0)
	{
		dt->str[1] = '.';
		i += 2;
		while (i < p + 2)
		{
			dt->str[i] = '0';
			i++;
		}
	}
	dt->str[i] = '\0';
	return ;
}

static void	ft_calc_base_10_ent(t_str *dt, register double nbr)
{
	register int	mod;
	register int	offset;

	offset = dt->size;
	while ((unsigned long long int)nbr != 0)
	{
		mod = (unsigned long long int)nbr % 10;
		nbr = nbr / 10 ;
		dt->str[offset - dt->idx] = mod + 48;
		dt->idx++;
	}
	return ;
}

static void	ft_calc_base_10_frac(t_str *dt, register double nbr
	, register int p)
{
	register int	i;

	dt->str[dt->size] = '.';
	dt->idx += dt->size;
	nbr -= (double)(unsigned long long int)nbr;
	i = 0;
	while (i < p)
	{
		nbr *= 10;
		dt->str[dt->idx] = (char)nbr + 48;
		nbr -= (double)(char)nbr;
		i++;
		dt->idx++;
	}	
	return ;
}

char	*ft_ftoa(double n, unsigned int p)
{
	t_str	dt;

	dt.size = ft_get_size((int)n);
	dt.str = ft_calloc ((dt.size + p + 2), sizeof (char));
	if (dt.str == NULL)
		return (NULL);
	if (n == 0)
	{
		null_str(&dt, p);
		return (dt.str);
	}
	dt.idx = 1;
	if (n < 0)
	{
		dt.str[0] = '-';
		n = -n;
	}
	ft_calc_base_10_ent(&dt, n);
	if (p != 0)
		ft_calc_base_10_frac(&dt, n, p);
	else
		dt.str[dt.size + p + 2] = '\0';
	return (dt.str);
}
