/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:00:43 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:34:55 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)

{
	unsigned char	*ps1;
	unsigned char	*ps2;
	register size_t	i;

	ps1 = (unsigned char *)(s1);
	ps2 = (unsigned char *)(s2);
	i = 0;
	while (i < n)
	{
		if (*ps1 != *ps2)
			return (*ps1 - *ps2);
		ps1++;
		ps2++;
		i++;
	}
	return (0);
}
