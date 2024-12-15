/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:38:56 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:40:48 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sbstr, size_t len)
{
	register size_t	len_s;

	if (!(str && sbstr) && len == 0)
		return (NULL);
	if (!sbstr || sbstr == str)
		return ((char *)str);
	len_s = ft_strlen(sbstr);
	while (*str && len_s <= len--)
	{
		if (!(ft_strncmp((char *)str, (char *)sbstr, len_s)))
			return ((char *)str);
		str++;
	}
	return (NULL);
}
