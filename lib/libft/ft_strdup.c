/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:46:49 by jveuille          #+#    #+#             */
/*   Updated: 2023/08/04 09:26:19 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*dstr;
	register size_t	i;
	register size_t	size;

	size = ft_strlen(s);
	dstr = malloc(sizeof(char) * (size + 1));
	if (dstr != NULL)
	{
		i = 0;
		while (i < size)
		{
			dstr[i] = s[i];
			i++;
		}
		dstr[i] = '\0';
		return (dstr);
	}
	return (NULL);
}
