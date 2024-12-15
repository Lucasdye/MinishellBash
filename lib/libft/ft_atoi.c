/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:15:12 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:27:19 by jveuille         ###   ########.fr       */
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

int	ft_atoi(const char *nptr)
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
			sign = sign * -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) && (nptr[i] != '\0'))
	{
		num = (num * 10) + (nptr[i] - 48);
		i++;
	}
	return (num * sign);
}
