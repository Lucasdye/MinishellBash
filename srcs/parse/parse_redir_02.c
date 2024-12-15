/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:36:28 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/30 10:21:52 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_trim_opt(t_data *dt, size_t *idx, t_idx *s_idx)
{
	s_idx->start = *idx;
	s_idx->end = s_idx->start;
	while ((dt->rt_line[s_idx->end] != '\0'
			&& (ft_iswhite_space(dt->rt_line[s_idx->end]) == true)))
	{
		s_idx->start++;
		(*idx)++;
		s_idx->end++;
	}
	return ;
}

static t_bool	ft_merge_opt(t_data *dt, char **s1, size_t *idx, t_idx s_idx)
{
	t_bool	ks;

	ks = false;
	if ((dt->rt_line[s_idx.start] != '\0')
		&& (dt->rt_line[s_idx.start] == '-'))
	{
		ks = set_str_arg(&dt->err, s1, "--");
		dt->parse.idx.start = s_idx.start + 1;
		return (ks);
	}
	if (get_substr(&dt->err, s1, dt->rt_line, s_idx) == true)
		return (true);
	*idx = s_idx.end - 1;
	dt->parse.idx.start = s_idx.end;
	dt->parse.idx.end = s_idx.end;
	return (false);
}

t_bool	ft_set_tk_redir_opt(t_data *dt, t_token *tk, size_t *idx, t_idx s_idx)
{
	register size_t	size;

	ft_trim_opt(dt, idx, &s_idx);
	ft_chk_filename(dt, &s_idx);
	size = s_idx.end - s_idx.start;
	if (size != 0)
	{
		if (ft_merge_opt(dt, &tk->arg[1], idx, s_idx) == true)
			return (true);
	}
	else
	{
		*idx = s_idx.end - 1;
		dt->parse.idx.start = *idx;
		dt->parse.idx.end = *idx;
	}
	return (false);
}
