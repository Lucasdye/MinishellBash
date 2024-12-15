/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:49:55 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:50:57 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_upcase_str(char *s_num)
{
	register int	i;

	i = 0;
	while (s_num[i] != '\0')
	{
		s_num[i] = ft_toupper(s_num[i]);
		i++;
	}
	return (s_num);
}

int	ft_abs(int nbr)
{
	if (nbr < 0)
		nbr = -nbr;
	return (nbr);
}
