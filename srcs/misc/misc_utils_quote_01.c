/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_quote_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:51:03 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:38:04 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_isquote(char c, register size_t type)
{
	char	*wtab;

	wtab = "\x22\x27";
	if (!c || type > 2)
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

t_chk_str	ft_chk_quote(char c)
{
	t_chk_str	t_chk;
	char		*wtab;

	wtab = "\x22\x27";
	t_chk = ft_srchstr(c, wtab);
	return (t_chk);
}

t_chk_str	ft_chk_str_quote(char *str)
{
	t_chk_str	t_chk;

	t_chk.ks = false;
	if (str)
	{
		if (str[0] == str[ft_strlen(str) - 1])
		{
			t_chk = ft_chk_quote(str[0]);
		}
	}
	return (t_chk);
}

t_chk_str_e	ft_chk_str_quote_01(char *str)
{
	register size_t	i;
	t_chk_str_e		chk;

	chk.ks = false;
	chk.s.ks = false;
	chk.s.idx = 0;
	if (str == NULL)
	{
		chk.ks = true;
		return (chk);
	}
	i = 0;
	while ((str[i] != '\0') && (chk.s.ks == false))
	{
		if (ft_isquote(str[i], ALL) == true)
			chk.s.ks = true;
		i++;
	}
	return (chk);
}
