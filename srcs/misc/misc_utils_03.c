/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:16:28 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:35:57 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_chk_str	ft_srchstr(char c, char *wtab)
{
	t_chk_str		t_chk;
	register size_t	i;

	t_chk.ks = false;
	t_chk.idx = 0;
	i = 0;
	while (wtab[i] != '\0')
	{
		if (c == wtab[i])
		{
			t_chk.ks = true;
			t_chk.idx = i;
			return (t_chk);
		}
		i++;
	}
	return (t_chk);
}

t_bool	ft_ischar_spec(char c, char *wtab, register size_t type)
{
	if (!c || type > ft_strlen(wtab))
		return (false);
	if (type == ALL)
	{
		if (ft_srchstr(c, wtab).ks == true)
			return (true);
	}
	else if (c == wtab[type - 1])
		return (true);
	return (false);
}

t_chk_str	ft_chk_spec(char c, char *wtab)
{
	t_chk_str	t_chk;

	t_chk = ft_srchstr(c, wtab);
	return (t_chk);
}

size_t	ft_find_tab_idx(char c, char *wtab)
{
	register size_t	i;

	i = 0;
	while (wtab[i] != '\0')
	{
		if (c == wtab[i])
			return (i);
		i++;
	}
	return (ERR);
}

t_bool	ft_isstr_whitespace(char *str)
{
	t_bool			ks;
	register size_t	i;

	i = 0;
	ks = true;
	if (str == NULL)
		return (false);
	while (str[i] != '\0' && (ks == true))
	{
		if (ft_iswhite_space(str[i]) == false)
			ks = false;
		i++;
	}
	return (ks);
}
