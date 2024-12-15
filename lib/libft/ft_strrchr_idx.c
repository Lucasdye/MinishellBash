/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr_idx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 07:08:43 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/27 07:49:06 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline static char	check(t_res *chk, char c1, char c2, register size_t i)
{
	if (c1 == c2)
	{	
		chk->ks = TRUE;
		chk->ret = (void *)i;
		return (TRUE);
	}
	return (FALSE);
}

t_res	ft_strrchr_idx(const char *s, int c)
{
	t_res			chk;
	register size_t	i;

	chk.ks = FALSE;
	chk.ret = NULL;
	if (s)
	{
		i = 0;
		while (s[i] != '\0')
			i++;
		while (i != 0)
		{
			if (check(&chk, s[i], (char)c, i) == TRUE)
				return (chk);
			i--;
		}
		check(&chk, s[i], (char)c, i);
	}
	return (chk);
}
