/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 07:47:13 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 16:33:19 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_srchstr(char str, char *wtab)
{
	register int	i;

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

inline static long	calc(const char *nptr, register long i,
	register long num, register int sign)
{
	char	ks_ovf;

	ks_ovf = FALSE;
	while ((ft_isdigit(nptr[i]) && (nptr[i] != '\0')) && ks_ovf == FALSE)
	{
		if ((((LLONG_MAX - (nptr[i] - 48)) / 10)
				< (unsigned)num) && (sign == 1))
		{
			num = LLONG_MAX;
			ks_ovf = TRUE;
		}
		else if ((((LLONG_MIN - (nptr[i] - 48)) / 10)
				< (unsigned)num) && (sign == -1))
		{
			num = LLONG_MIN;
			ks_ovf = TRUE;
		}
		else
			num = (num * 10) + (nptr[i] - 48);
		i++;
	}
	return (num);
}

long	ft_atol(const char *nptr)
{
	register int	sign;
	register long	i;
	register long	num;

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
	num = calc(nptr, i, num, sign);
	return (num * sign);
}
