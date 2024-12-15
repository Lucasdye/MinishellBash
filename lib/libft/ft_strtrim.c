/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:10:29 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:41:17 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_chkfind_set(char const *str, char const *set, size_t start)
{
	register size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (str[start] == set[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_res;
	size_t	len_s1;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	len_s1 = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_chkfind_set(s1, set, i))
		i++;
	j = len_s1;
	while ((j > i) && ft_chkfind_set(s1, set, j - 1))
		j--;
	str_res = ft_substr((char *)s1, (unsigned int)i, j);
	if (str_res == NULL)
		return (NULL);
	str_res[j - i] = '\0';
	return (str_res);
}
