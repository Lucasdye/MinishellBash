/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_white_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:45:34 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/12 15:27:04 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_skip_whitespace(const char *str, register size_t idx)
{
	if (str == NULL)
		return (idx);
	else if (idx > ft_strlen(str))
		return (idx);
	else
	{
		while ((str[idx] != '\0') && (ft_iswhite_space(str[idx]) == true))
			idx++;
	}
	return (idx);
}

t_chk_str	ft_skip_whitespace_s(const char *str, register size_t idx)
{
	t_chk_str	chk;

	chk.ks = false;
	chk.idx = idx;
	if (str == NULL)
		chk.ks = true;
	else if (idx > ft_strlen(str))
		chk.ks = true;
	else
	{
		while ((str[chk.idx] != '\0')
			&& (ft_iswhite_space(str[chk.idx]) == true))
			chk.idx++;
	}
	return (chk);
}
