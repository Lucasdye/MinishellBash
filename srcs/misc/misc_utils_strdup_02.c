/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_strdup_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:12:00 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:37:25 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_t_dup(t_dup *src)
{
	src->str = NULL;
	src->ptr = 0;
	src->size = 0;
	return ;
}

t_dup	ft_dupjoint(char *s1, char *s2, char c, size_t start)
{	
	t_dup	dest;

	ft_init_t_dup(&dest);
	if (s1 || s2)
	{
		if (s1)
		{
			dest = ft_strdup_obj(s1, c, start, ft_strlen(s1));
			if (dest.str == NULL)
				return (dest);
		}
		if (s2)
		{
			dest.str = ft_strjoin_m(dest.str, s2);
			if (dest.str != NULL)
				dest.size += ft_strlen(s2);
			else
				ft_init_t_dup(&dest);
		}
	}
	return (dest);
}
