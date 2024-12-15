/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:59:33 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/12 15:26:47 by jveuille         ###   ########.fr       */
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
			return (true);
		}
		i++;
	}
	return (false);
}

static char	ft_white_space(char str)
{
	char	*wtab;

	wtab = "\x20\t\n\v\f\r";
	return (ft_srchstr(str, wtab));
}

inline static int	calc(const char *nptr, register int i,
	register int num, register int sign)
{
	char	ks_ovf;

	ks_ovf = FALSE;
	while ((ft_isdigit(nptr[i]) && (nptr[i] != '\0')) && ks_ovf == FALSE)
	{
		if ((((INT_MAX - (nptr[i] - 48)) / 10)
				< num) && (sign == 1))
		{
			num = INT_MAX;
			ks_ovf = TRUE;
		}
		else if ((((INT_MIN - (nptr[i] - 48)) / 10)
				< num) && (sign == -1))
		{
			num = INT_MIN;
			ks_ovf = TRUE;
		}
		else
			num = (num * 10) + (nptr[i] - 48);
		i++;
	}
	return (num);
}

int	ft_atoi_m(const char *nptr)
{
	register int	sign;
	register int	i;
	register int	num;

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
