/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:16:16 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:40:02 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	register size_t	i;
	register size_t	j;
	register size_t	srclen;
	register size_t	destlen;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dst);
	i = 0;
	j = destlen;
	if (((destlen) < (size - 1)) && (size > 0))
	{
		while ((src[i] != '\0') && ((destlen + i) < (size - 1)))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	if (destlen >= size)
		destlen = size;
	return (destlen + srclen);
}
