/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 08:37:08 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:34:39 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	register size_t	i;

	if (s)
	{
		i = 0;
		while (i < n)
		{
			if (*(unsigned char *)(s + i) == (unsigned char)c)
			{
				return ((void *)(s + i));
			}
			i++;
		}		
	}
	return (NULL);
}
