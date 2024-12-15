/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 07:52:42 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:41:33 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)

{
	char			*substr;
	register size_t	rlsize;
	register size_t	i;

	if (!s)
		return (NULL);
	rlsize = ft_strlen(s);
	if (start > rlsize)
		rlsize = 0;
	else if (len > (rlsize - start))
		rlsize -= start;
	else
		rlsize = len;
	substr = ft_calloc(rlsize + 1, 1);
	if (!substr)
		return (NULL);
	i = 0;
	while ((i < len) && (start <= ft_strlen(s)))
		substr[i++] = s[start++];
	return (substr);
}
