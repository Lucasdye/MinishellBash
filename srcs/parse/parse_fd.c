/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 08:49:06 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/18 16:35:32 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_set_tk_fd(t_data *dt, t_str *s_tmp)
{
	dt->parse.idx.end = dt->parse.idx.start;
	while (ft_ischar_spec(dt->rt_line[dt->parse.idx.end]
			, MSHL_SEP_FDO, ALL) == false)
		dt->parse.idx.end++;
	if (get_substr(&dt->err, &s_tmp->str, dt->rt_line, dt->parse.idx) == true)
		return (false);
	if (set_token(dt, s_tmp->str, tk_fd, none) == true)
		return (true);
	dt->parse.idx.start = dt->parse.idx.end;
	return (false);
}

static t_bool	ft_tokenize_fd(t_data *dt, t_str *s_tmp, t_idx istr
	, size_t *idx)
{
	size_t	size;

	size = istr.start - dt->parse.idx.start;
	while (ft_iswhite_space(dt->rt_line[*idx]) == true)
		(*idx)++;
	if ((dt->rt_line[*idx] == '\0') && (size == 0) && (dt->parse.tk.idx == 0))
	{
		if (dt->rt_line[*idx] == '\0')
			(*idx)--;
		return (false);
	}
	if (istr.start != 0)
		istr.start--;
	istr.end = istr.start;
	if (store_tk_str(dt, s_tmp, &istr.start, false) == true)
		return (false);
	if (ft_set_tk_fd(dt, s_tmp) == true)
		return (false);
	return (true);
}

t_bool	ft_chk_tk_fd(t_data *dt, t_str *s_tmp, size_t	*idx)
{
	t_idx	istr;
	t_bool	ks;

	ks = true;
	istr.start = *idx;
	if (*idx != 0)
	{
		if ((ft_ischar_spec(dt->rt_line[*idx - 1], MSHL_SEP_FDI, ALL) == false)
			|| (ft_iswhite_space(dt->rt_line[*idx - 1]) == false))
			ks = false;
	}
	while (ft_isdigit(dt->rt_line[*idx]) == true)
		(*idx)++;
	if ((ks == false)
		|| (ft_ischar_spec(dt->rt_line[*idx], MSHL_SEP_FDO, ALL) == false))
	{
		(*idx)--;
		return (false);
	}
	if (ft_tokenize_fd(dt, s_tmp, istr, idx) == false)
		return (false);
	free_tstr(s_tmp);
	return (true);
}
