/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:57:31 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/10 14:47:38 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static t_bool	ft_init_tk_arg(t_data *dt, register size_t subtype)
{
	int		size;

	size = 3;
	dt->parse.tk.tab[dt->parse.tk.idx - 1].arg = ft_calloc(size,
			sizeof(*dt->parse.tk.tab[dt->parse.tk.idx - 1].arg));
	if (dt->parse.tk.tab[dt->parse.tk.idx - 1].arg == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	if (dt->parse.rtab[subtype].opt == false)
	{
		if (set_str_arg(&dt->err
				, &dt->parse.tk.tab[dt->parse.tk.idx - 1].arg[1], "-" ) == true)
			return (true);
	}
	return (false);
}

inline static t_bool	ft_create_tk_redir(t_data *dt, register size_t subtype)
{
	if ((dt->parse.tk.idx != 0)
		&& (dt->parse.tk.tab[dt->parse.tk.idx - 1].type == tk_fd))
	{
		if (set_str_arg(&dt->err, &dt->tmp.str
				, dt->parse.tk.tab[dt->parse.tk.idx - 1].name) == true)
			return (true);
		free(dt->parse.tk.tab[dt->parse.tk.idx - 1].name);
		if (set_str_arg(&dt->err, &dt->parse.tk.tab[dt->parse.tk.idx - 1].name
				, dt->parse.rtab[subtype].str) == true)
			return (true);
		dt->parse.tk.tab[dt->parse.tk.idx -1].type = tk_redir_op;
		dt->parse.tk.tab[dt->parse.tk.idx -1].subtype = subtype;
	}
	else
	{
		if (set_str_arg(&dt->err, &dt->tmp.str
				, dt->parse.rtab[subtype].rdr) == true)
			return (true);
		if (set_token(dt, dt->parse.rtab[subtype].str
				, tk_redir_op, subtype) == true)
			return (true);
	}
	dt->parse.idx.end = dt->parse.idx.start + dt->parse.rtab[subtype].size - 1;
	dt->parse.idx.start = dt->parse.idx.end + 1;
	return (false);
}

static t_bool	ft_set_tk_redir(t_data *dt, register size_t subtype, size_t *idx
	, t_idx s_idx)
{
	if (ft_create_tk_redir(dt, subtype) == true)
		return (true);
	if (dt->rt_line[*idx + dt->parse.rtab[subtype].size] != '\0')
		*idx += dt->parse.rtab[subtype].size;
	else
		*idx += dt->parse.rtab[subtype].size - 1;
	if (ft_init_tk_arg(dt, subtype) == true)
		return (true);
	if (set_str_arg(&dt->err, &dt->parse.tk.tab[dt->parse.tk.idx - 1].arg[0]
			, dt->tmp.str) == true)
		return (true);
	if (dt->parse.rtab[subtype].opt == true)
	{
		if (ft_set_tk_redir_opt(dt, &dt->parse.tk.tab[dt->parse.tk.idx - 1]
				, idx, s_idx) == true)
			return (true);
	}
	else if (dt->parse.tk.tab[dt->parse.tk.idx - 1].subtype != redir_pipe)
	{
		if (ft_chk_tk_file(dt, idx, s_idx) == true)
			return (true);
	}
	else
		idx -= 1;
	return (false);
}

t_bool	ft_chk_tk_redir(t_data *dt, size_t *idx)
{
	register size_t	i;
	t_chk_str		chk;
	t_idx			s_idx;
	t_bool			ks;

	ks = false;
	chk.ks = false;
	s_idx.start = *idx;
	i = 0;
	while (i < MSHL_REDIR_NUM)
	{
		s_idx.end = *idx + dt->parse.rtab[i].size;
		if (get_substr(&dt->err, &dt->tmp.str, dt->rt_line, s_idx) == true)
			return (true);
		if (ft_strchk(dt->parse.rtab[i].str, dt->tmp.str) == true)
		{
			chk.ks = true;
			chk.idx = i;
		}
		i++;
		free(dt->tmp.str);
	}
	if (chk.ks == true)
		ks = ft_set_tk_redir(dt, chk.idx, idx, s_idx);
	return (free(dt->tmp.str), ks);
}
