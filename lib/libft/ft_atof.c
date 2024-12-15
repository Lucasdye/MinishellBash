/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:18:07 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 16:32:59 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <float.h>

static char	ft_srchstr(char str, char *wtab)
{
	register int		i;

	i = 0;
	while (wtab[i] != '\0')
	{
		if (str == wtab[i])
		{
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static char	ft_white_space(char str)
{
	char	*wtab;

	wtab = "\x20\t\n\v\f\r";
	return (ft_srchstr(str, wtab));
}

inline static double	calc_frac(const char *nptr, int i,
	register double num, int sign)
{
	register double	j;
	char			ks_ovf;

	ks_ovf = FALSE;
	j = 10;
	while ((ft_isdigit(nptr[i]) && (nptr[i] != '\0')) && ks_ovf == FALSE)
	{
		if ((((DBL_MAX - (nptr[i] - 48)) / j)
				< (unsigned)num) && (sign == 1))
		{
			num = DBL_MAX;
			ks_ovf = TRUE;
		}
		else if ((((DBL_MIN - (nptr[i] - 48)) / j)
				< (unsigned)num) && (sign == -1))
		{
			num = DBL_MIN;
			ks_ovf = TRUE;
		}
		else
		num = num + ((nptr[i] - 48) / j);
		i++;
		j *= 10;
	}
	return (num);
}

inline static long	calc_ent(const char *nptr, int *i,
	register long num, register int sign)
{
	char	ks_ovf;

	ks_ovf = FALSE;
	while ((ft_isdigit(nptr[*i]) && (nptr[*i] != '\0')) && ks_ovf == FALSE)
	{
		if ((((LLONG_MAX - (nptr[*i] - 48)) / 10)
				< (unsigned)num) && (sign == 1))
		{
			num = LLONG_MAX;
			ks_ovf = TRUE;
		}
		else if ((((LLONG_MIN - (nptr[*i] - 48)) / 10)
				< (unsigned)num) && (sign == -1))
		{
			num = LLONG_MIN;
			ks_ovf = TRUE;
		}
		else
			num = (num * 10) + (nptr[*i] - 48);
		*i = *i + 1;
	}
	return (num);
}

double	ft_atof(const char *nptr)
{
	register int	sign;
	int				i;
	register double	num;

	sign = 1;
	i = 0;
	num = 0;
	while (ft_white_space(nptr[i]) == TRUE)
		i++;
	if ((nptr[i] == '-' || nptr[i] == '+') && nptr[i])
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	if (nptr[i] != '.')
		num = calc_ent(nptr, &i, num, sign);
	else
	{
		i++;
		num = calc_frac(nptr, i, num, sign);
	}
	return (num * sign);
}
