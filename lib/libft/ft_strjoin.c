/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 08:33:46 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 16:37:28 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	register size_t	len_s1;
	register size_t	len_s2;

	if (s1 || s2)
	{
		if (!s1)
			return ((char *)s2);
		if (!s2)
			return ((char *)s1);
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		str = (char *)malloc(sizeof (char) * (len_s1 + len_s2 + 1));
		if (str != NULL)
		{
			ft_strlcpy(str, s1, len_s1 + 1);
			ft_strlcat(str, s2, (len_s1 + len_s2 + 1));
			return (str);
		}
	}
	return (NULL);
}
