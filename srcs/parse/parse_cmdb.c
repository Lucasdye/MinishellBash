/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:22:11 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/17 11:02:59 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_chk_stab	ft_isstr_ftab_sz(char *s1, t_func_cmdb *tab
	, register size_t size)
{
	t_chk_stab		chk;
	register size_t	i;
	t_bool			ks;

	ks = false;
	i = 0 ;
	while ((i < size) && (ks == false))
	{
		if (ft_strchk(s1, tab[i].name) == true)
			ks = true;
		else
			i++;
	}
	chk.ks = ks;
	chk.idx = i;
	return (chk);
}

static t_bool	ft_tokenize_cmd(t_data *dt, t_str *s1, t_str s_tmp)
{
	t_chk_stab		chk;
	t_bool			ks;

	ks = false;
	if (ft_isstr_whitespace(s_tmp.str) == false)
	{
		dt->parse.icmd.ks = true;
		dt->parse.icmd.idx = dt->parse.tk.idx;
		chk = ft_isstr_ftab_sz(s_tmp.str, dt->parse.ftab, MSHL_CMD_B_NUM);
		if (chk.ks == true)
		{
			if (set_token(dt, s1->str, tk_cmd_b, chk.idx) == true)
				ks = true;
		}
		else if (set_token(dt, s1->str, tk_cmd, none) == true)
		ks = true;
	}
	return (ks);
}

t_bool	ft_set_tk_cmdb(t_data *dt, t_str *s1)
{
	register t_idx	s_idx;
	t_str			s_tmp;
	t_bool			ks;

	s_idx.start = 0;
	s_idx.end = 0;
	ks = false;
	s1->str = ft_clean_white_space_qt(s1->str);
	while ((ft_iswhite_space(s1->str[s_idx.end]) == false)
		&& (s_idx.end < (s1->size)))
		s_idx.end++;
	s_tmp.size = s_idx.end - s_idx.start;
	if (get_substr(&dt->err, &s_tmp.str, s1->str, s_idx) == true)
		return (true);
	ks = ft_tokenize_cmd(dt, s1, s_tmp);
	free_tstr(s1);
	free_tstr(&s_tmp);
	return (ks);
}
