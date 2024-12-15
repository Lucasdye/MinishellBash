/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:17:48 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 10:10:10 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	init_parse_data(t_data *dt, t_str *s_tmp)
{
	dt->parse.icmd.ks = false;
	dt->parse.icmd.idx = 0;
	dt->parse.tk.size = MSHL_TK_TAB_NB;
	dt->parse.tk.idx = 0;
	dt->parse.tk.nbr = 0;
	ft_init_flg_quote(&dt->parse.quote);
	dt->parse.is_redir = false;
	dt->parse.idx.start = 0;
	dt->parse.idx.end = 0;
	dt->parse.nbr_bk = 1;
	dt->parse.err_space = false;
	if (init_tk_tab(dt, &dt->parse.tk.tab, dt->parse.tk.size) == true)
		return (true);
	s_tmp->size = ft_strlen(dt->rt_line);
	s_tmp->idx = 0;
	s_tmp->str = NULL;
	return (false);
}

t_chk_str	parse_tk_fd(t_data *dt, t_str *s_tmp, size_t *idx)
{
	t_chk_str	chk;

	chk.ks = false;
	chk.idx = false;
	if (ft_isdigit(dt->rt_line[*idx]) == true)
	{
		if (ft_chk_tk_fd(dt, s_tmp, idx) == false)
		{
			if (dt->err.v.ks == true)
			{
				chk.ks = true;
				return (chk);
			}
			(*idx)++;
			chk.idx = true;
			return (chk);
		}
	}
	return (chk);
}

static t_chk_str	ft_tokenize_all(t_data *dt, t_str *s_tmp, size_t *i)
{
	t_chk_str	chk;

	chk.ks = false;
	chk.idx = false;
	if (ft_iswhite_space(dt->rt_line[*i]) == false)
	{
		chk = parse_tk_fd(dt, s_tmp, i);
		if ((chk.ks == true) || (chk.idx == true))
			return (chk);
		if (store_tk_str(dt, s_tmp, i, false) == false)
		{
			if (ft_set_tk_sep(dt, i) == false)
			{
				if (ft_ischar_spec(dt->rt_line[*i], MSHL_REDIR, ALL) == true)
					chk.ks = ft_chk_tk_redir(dt, i);
				return (chk);
			}
		}
		chk.ks = true;
	}
	return (chk);
}

static t_bool	parse_core(t_data *dt, t_str *s_tmp, t_chk_str chk, size_t *i)
{
	while ((*i < dt->size))
	{
		if (((ft_ischar_spec(dt->rt_line[*i], MSHL_SPEC, ALL) == true)
				|| (ft_isdigit(dt->rt_line[*i]) == true))
			&& (dt->parse.quote.ks == false))
		{
			chk = ft_tokenize_all(dt, s_tmp, i);
			if (chk.ks == true)
				return (true);
			if (chk.idx == true)
				continue ;
		}
		else if (ft_isquote(dt->rt_line[*i], ALL) == true)
			ft_set_flg_quote(&dt->parse.quote, dt->rt_line[*i]);
		if ((dt->parse.tk.tab[dt->parse.tk.idx].type == tk_sep)
			&& ((char)dt->parse.tk.tab[dt->parse.tk.idx].subtype
				== MSHL_SEP_I[c_inst]))
		{	
			if (ft_ctrl_tk_quote(dt) == true)
				return (true);
		}
		if (*i < dt->size)
			(*i)++;
	}
	return (false);
}

t_bool	parse_rt_line(t_data *dt)
{
	size_t		i;
	t_str		s_tmp;
	t_chk_str	chk;
	t_bool		ks;

	chk.ks = false;
	chk.idx = false;
	i = 0;
	init_struct_hd_exec(dt);
	if (dt->rt_line == NULL)
		return (false);
	if (init_parse_data(dt, &s_tmp) == false)
	{
		if (parse_core(dt, &s_tmp, chk, &i) == false)
		{
			store_tk_str(dt, &s_tmp, &i, true);
			ks = ft_ctrl_tk_quote(dt);
			free(s_tmp.str);
			return (ks);
		}
	}
	return (true);
}
