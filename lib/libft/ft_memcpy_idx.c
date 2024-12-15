/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_idx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:42:31 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 16:35:58 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* memcopy with start idx , n char  */
void	*ft_memcpy_idx(void *dest, const void *src, size_t start, size_t n)
{
	register size_t	i;

	if (!(dest && src))
		return (dest);
	if (n != 0)
	{
		i = 0;
		while (i < n)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + start + i);
			i++;
		}
	}
	return (dest);
}
