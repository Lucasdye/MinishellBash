/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:24:40 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 10:10:31 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	t_bool	ft_set_space_str(t_data *dt, char **s_line, size_t *idx
	, size_t size)
{
	t_idx	s_idx;
	char	ks;
	char	*s_tmp;

	s_tmp = NULL;
	s_idx.start = *idx + size;
	s_idx.end = dt->size;
	if (get_substr(&dt->err, &s_tmp, dt->rt_line, s_idx) == false)
	{
		if (ft_strjcat(s_line, s_tmp) == false)
		{
			*idx += size;
			dt->size++;
			free(dt->rt_line);
			ks = set_str_arg(&dt->err, &dt->rt_line, *s_line);
			free_str(s_line);
			free(s_tmp);
			return (ks);
		}
		free(s_tmp);
	}
	return (true);
}

static t_bool	ft_add_space(t_data *dt, size_t *idx, size_t size)
{
	t_idx	s_idx;
	char	*s_tmp;
	char	*s_line;

	s_tmp = NULL;
	s_line = NULL;
	s_idx.start = 0;
	s_idx.end = *idx + size;
	if (get_substr(&dt->err, &s_tmp, dt->rt_line, s_idx) == true)
		return (true);
	if (ft_strjcat(&s_line, s_tmp) == false)
	{
		free_str(&s_tmp);
		if (ft_strjcat(&s_line, "\x20") == false)
		{
			if (ft_set_space_str(dt, &s_line, idx, size) == true)
				return (true);
			return (false);
		}
		free_str(&s_tmp);
	}
	return (true);
}

static t_bool	ft_is_redir_str_01(t_data *dt, size_t *idx)
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
		free_str(&dt->tmp.str);
	}
	if (chk.ks == true)
		ks = ft_add_space(dt, idx, dt->parse.rtab[chk.idx].size);
	return (ks);
}

t_bool	ft_conform_str(t_data *dt)
{
	size_t		i;
	t_quote		qt;

	i = 0;
	ft_init_flg_quote(&qt);
	while (i < dt->size)
	{
		if (ft_isquote(dt->rt_line[i], ALL) == true)
			ft_set_flg_quote(&qt, dt->rt_line[i]);
		if ((qt.ks == false)
			&& (ft_ischar_spec(dt->rt_line[i], MSHL_REDIR, ALL) == true))
		{
			if (ft_is_redir_str_01(dt, &i) == true)
				return (true);
		}
		i++;
	}
	return (false);
}
