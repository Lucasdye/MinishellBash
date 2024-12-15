/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:53:28 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:26:34 by jveuille         ###   ########.fr       */
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

static int	calc_hex(const char *nptr, register int i, register int num)
{
	register char	ks_ovf;
	register int	offset;

	ks_ovf = FALSE;
	while ((ft_ishexa(nptr[i]) && (nptr[i] != '\0')) && ks_ovf == FALSE)
	{
		if (nptr[i] < 58)
			offset = 48;
		else if (nptr[i] < 71)
			offset = 55;
		else
			offset = 97;
		if (((INT_MAX - (nptr[i] - offset)) / 16) < (num))
		{
			num = INT_MAX ;
			ks_ovf = TRUE;
		}
		else
			num = (num * 16) + (nptr[i] - offset);
		i++;
	}
	return (num);
}

int	ft_atoh(const char *nptr)
{
	register int	i;
	register int	j;
	unsigned int	num;

	num = 0;
	if (nptr == NULL)
		return (num);
	i = 0;
	while (ft_white_space(nptr[i]) == TRUE)
		i++;
	j = 0;
	while (nptr[i + j] != '\0')
		j++;
	if (j < 3)
		return (num);
	if ((nptr[i] != '0') || (nptr[i +1] != 'x'))
		return (num);
	j = 2;
	while (nptr[i + j] != '\0')
	{
		if (ft_ishexa(nptr[i + j]) == (FALSE))
			return (num);
		j++;
	}
	return ((int)calc_hex(nptr, (i +2), num));
}
