/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:45:39 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/18 13:30:42 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ks_stab	ft_chk_sep(t_data *dt, size_t idx)
{
	register size_t	i;
	t_ks_stab		chk;

	chk.ks = false;
	chk.idx = 1;
	while (chk.idx < MSHL_SEP_NUM)
	{
		chk.size = ft_strlen(dt->parse.stab[chk.idx].str);
		if (chk.size != 0)
		{
			i = 0;
			while ((i < chk.size)
				&& (dt->rt_line[idx + i] == dt->parse.stab[chk.idx].str[i]))
				i++;
			if ((i == chk.size)
				&& (dt->rt_line[idx] == dt->parse.stab[chk.idx].str[i - 1]))
			{
				chk.ks = true;
				dt->parse.idx.end += chk.size - 1;
				return (chk);
			}
		}
		chk.idx++;
	}
	return (chk);
}

t_bool	ft_set_tk_sep(t_data *dt, size_t *idx)
{
	t_ks_stab	chk;
	char		*str;

	dt->parse.idx.start = *idx;
	chk = ft_chk_sep(dt, *idx);
	if (chk.ks == true)
	{
		if (set_str_arg(&dt->err, &str, dt->parse.stab[chk.idx].str) == true)
			return (true);
		if (set_token(dt, str, tk_sep, chk.idx) == true)
		{
			free(str);
			return (true);
		}
		if (chk.idx == c_inst)
			dt->parse.icmd.ks = false;
		*idx = dt->parse.idx.end + 1;
		dt->parse.idx.start = dt->parse.idx.end + 1;
		free(str);
	}
	return (false);
}
