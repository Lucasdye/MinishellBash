/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_strdup_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:18:24 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/20 13:12:34 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dup	ft_strdup_obj(const char *s, int c, register size_t s_idx_init
	, register size_t s_idx_max)
{
	t_dup	dst;

	if (!s || (s_idx_init > s_idx_max))
	{
		dst.str = NULL;
		return (dst);
	}
	dst.ptr = s_idx_init;
	while ((dst.ptr < s_idx_max) && (s[dst.ptr] != (char)c))
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

t_bool	ft_strjcat_obj(t_dup *dest, t_dup *src)
{
	t_dup	tmp;

	tmp.str = NULL;
	if (dest->str == NULL)
	{
		dest->str = ft_calloc((src->size + 1), sizeof(char));
		if (dest->str == NULL)
			return (true);
		dest->ptr = 0;
		dest->size = ft_strlcat_obj(*dest, *src, (src->size +1));
	}
	else
	{
		*dest = ft_strjoin_obj(*dest, *src);
		if (dest->str == NULL)
			return (true);
		free(tmp.str);
	}
	return (false);
}
