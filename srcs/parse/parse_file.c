/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:03:03 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 15:05:55 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_chk_filename(t_data *dt, t_idx *s_idx)
{
	t_bool		ks;
	t_quote		qt;
	t_chk_str	chk;

	ks = false;
	ft_init_flg_quote(&qt);
	while ((dt->rt_line[s_idx->end] != '\0') && (ks == false)
		&& !((ft_iswhite_space(dt->rt_line[s_idx->end]) == true)
			&& (qt.ks == false)))
	{
		chk = ft_chk_quote(dt->rt_line[s_idx->end]);
		if (chk.ks == true)
			ft_set_flg_quote(&qt, dt->rt_line[s_idx->end]);
		if (qt.ks == false)
		{
			ks = ft_ischar_spec(dt->rt_line[s_idx->end], MSHL_FILE, ALL);
			if (ks == false)
				s_idx->end++;
		}
		else
			s_idx->end++;
	}
	return ;
}

static t_bool	ft_tokenize_file(t_data *dt, size_t *idx, t_idx s_idx)
{
	char	*s1;

	s1 = NULL;
	if (get_substr(&dt->err, &s1, dt->rt_line, s_idx) == true)
		return (true);
	if (set_token(dt, s1, tk_file, none) == true)
	{
		free_str(&s1);
		return (true);
	}
	free(s1);
	*idx = s_idx.end -1;
	dt->parse.idx.start = s_idx.end;
	dt->parse.idx.end = s_idx.end;
	return (false);
}

t_bool	ft_chk_tk_file(t_data *dt, size_t *idx, t_idx s_idx)
{
	s_idx.start = *idx;
	ft_trim_opt(dt, idx, &s_idx);
	ft_chk_filename(dt, &s_idx);
	if (ft_tokenize_file(dt, idx, s_idx) == true)
		return (true);
	return (false);
}
