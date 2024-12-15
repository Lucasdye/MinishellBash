/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_white_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:51:22 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/17 11:10:06 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim_white_space(char *src)
{
	register size_t	j;
	register size_t	size;

	if (src == NULL)
		return (src);
	size = ft_strlen(src);
	while ((size > 0) && (ft_iswhite_space(src[0]) == true))
	{
		ft_memmove(&src[0], &src[1], size);
		size--;
	}
	j = size;
	while ((size > 0) && (ft_iswhite_space(src[j - 1]) == true))
	{
		ft_memmove(&src[j - 1], &src[j], (size - j + 1));
		j--;
		size--;
	}
	return (src);
}

char	*ft_clean_white_space(char *src)
{
	register size_t	i;
	register size_t	size;

	i = 0;
	if (src == NULL)
		return (src);
	src = ft_trim_white_space(src);
	size = ft_strlen(src);
	while (i < (size))
	{
		while ((i < size) && (ft_iswhite_space(src[i]) == false))
			i++;
		if (i < size)
		{
			src[i] = '\x20';
			i++;
			while ((i < size) && (ft_iswhite_space(src[i]) == true))
			{
				ft_memmove(&src[i], &src[i + 1], (size - i));
				size--;
			}
		}
	}
	return (src);
}
