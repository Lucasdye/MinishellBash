/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:12:45 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/17 11:06:22 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_m(size_t elcount, size_t elsize)
{
	void			*pstr;
	register size_t	i;

	if (elsize > 0 && (SIZE_MAX / elsize) < elcount)
		return (NULL);
	pstr = (void *)malloc(elcount * elsize);
	if (pstr != NULL)
	{
		i = 0;
		while (i < elcount)
		{
			*(char *)(pstr + i) = '\0';
			i++;
		}
		return (pstr);
	}
	return (NULL);
}

t_dup	ft_strdup_m(const char *s, int c, register size_t s_idx_init
	, register size_t s_idx_max)
{
	t_dup	dst;

	if (!(s && s_idx_max) || (s_idx_init > s_idx_max))
	{
		dst.str = NULL;
		return (dst);
	}
	dst.ptr = s_idx_init;
	while ((dst.ptr < s_idx_max) && (s[dst.ptr] != (char)c))
		dst.ptr++;
	if ((dst.ptr < s_idx_max) && (s[dst.ptr] == (char)c))
		dst.ptr++;
	dst.str = malloc(sizeof(char) * ((dst.ptr - s_idx_init) + 1));
	if (dst.str != NULL)
	{
		dst.size = 0;
		while (dst.size < (dst.ptr - s_idx_init))
		{
			dst.str[dst.size] = s[s_idx_init + dst.size];
			dst.size++;
		}
		dst.str[dst.size] = '\0';
	}
	return (dst);
}

size_t	ft_strlcat_obj(t_dup dst, const t_dup src, register size_t size)
{
	register size_t	i;
	register size_t	j;

	i = 0;
	j = dst.ptr;
	if (((dst.ptr) < (size - 1)) && (size > 0))
	{
		while ((src.str[i] != '\0') && ((dst.ptr + i) < (size - 1)))
		{
			dst.str[j] = src.str[i];
			i++;
			j++;
		}
	}
	dst.str[j] = '\0';
	if (dst.ptr >= size)
		dst.ptr = size;
	return (dst.ptr + src.size);
}

t_dup	ft_strjoin_obj(t_dup const s1, t_dup const s2)
{
	t_dup	dst;

	dst.str = NULL;
	dst.ptr = 0;
	if (s1.str || s2.str)
	{
		if (!s1.str)
			return (s2);
		if (!s2.str)
			return (s1);
		dst.str = (char *)malloc(sizeof (char) * (s1.size + s2.size + 1));
		if (dst.str != NULL)
		{
			dst.size = ft_strlcat_obj(dst, s1, (s1.size + 1));
			dst.ptr = dst.size;
			free(s1.str);
			dst.size = ft_strlcat_obj(dst, s2, (s1.size + s2.size + 1));
			return (dst);
		}
	}
	return (dst);
}
