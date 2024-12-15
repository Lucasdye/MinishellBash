/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:54:56 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 14:58:50 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	register size_t	i;

	i = 0;
	if (s != 0)
	{
		while (i < n)
		{
			*(unsigned char *)(s + i) = c;
			i++;
		}
		return (s);
	}
	else
	{
		return (NULL);
	}
}
