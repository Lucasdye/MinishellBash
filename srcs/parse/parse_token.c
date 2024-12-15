/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:42:04 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/10 16:16:47 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_tokenize_str(t_data *dt, t_str *s_tmp, size_t *idx)
{
	t_chk_str	chk;

	chk.ks = false;
	chk.idx = false;
	if (s_tmp->size != 0)
	{
		chk = parse_tk_fd(dt, s_tmp, idx);
		if (chk.ks == true)
			return (true);
		if (dt->parse.icmd.ks == false)
		{
			if (ft_set_tk_cmdb(dt, s_tmp) == true)
				return (true);
		}
		else if (ft_chk_tk_word(dt, s_tmp) == true)
			return (true);
		dt->parse.idx.start = dt->parse.idx.end + 1;
	}
	return (false);
}

static t_bool	ft_iscmd_redir(t_data *dt)
{
	if (dt->parse.tk.idx == 0)
		return (true);
	if ((dt->parse.tk.tab[dt->parse.tk.idx - 1].type == tk_redir_op)
		&& (dt->parse.tk.tab[dt->parse.tk.idx - 1].subtype == redir_pipe))
	{	
		dt->parse.nbr_bk += 1;
		dt->parse.icmd.ks = false;
		return (true);
	}
	if (dt->parse.tk.tab[dt->parse.tk.idx - 1].type == tk_sep)
		return (true);
	if (dt->parse.tk.tab[dt->parse.tk.idx - 1].type == tk_file)
		return (true);
	if ((dt->parse.tk.tab[dt->parse.tk.idx - 1].type == tk_redir_op)
		&& ((dt->parse.tk.tab[dt->parse.tk.idx - 1].subtype == redir_movin)
			|| (dt->parse.tk.tab[dt->parse.tk.idx - 1].subtype
				== redir_movout)))
		return (true);
	return (false);
}

static t_bool	ft_chk_tk_cond(t_data *dt, size_t *idx, t_bool ks
	, t_bool ks_end)
{
	if (((ks == false) && (dt->parse.quote.dir == out))
		|| ((ks == true) && (dt->parse.quote.dir == in)
			&& (dt->rt_line[*idx] == dt->parse.quote.type))
		|| ((ks == true) && (dt->parse.quote.dir == out)
			&& (dt->parse.quote.type == '\0'))
		|| (ks_end == true))
		return (true);
	return (false);
}

t_bool	store_tk_str(t_data *dt, t_str *s_tmp, size_t *idx, t_bool ks_end)
{
	t_bool	ks;

	dt->parse.idx.end = *idx;
	s_tmp->size = dt->parse.idx.end - dt->parse.idx.start;
	if (s_tmp->size > 0)
	{
		ks = ft_isquote(dt->rt_line[*idx], ALL);
		if (ft_chk_tk_cond(dt, idx, ks, ks_end) == true)
		{
			if (get_substr(&dt->err, &s_tmp->str, dt->rt_line,
					dt->parse.idx) == true)
				return (true);
			if (!((ks == true) && (dt->parse.quote.dir == in))
				&& (ft_iscmd_redir(dt)))
			{
				if (ft_tokenize_str(dt, s_tmp, idx) == true)
					return (true);
			}
			if (dt->parse.is_redir == true)
				dt->parse.is_redir = false;
		}
	}
	return (false);
}
