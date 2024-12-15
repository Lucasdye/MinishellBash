/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:01:17 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/25 07:45:57 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_set_tk_var_01(t_data *dt, register size_t idx)
{
	t_str			s_tmp;
	register size_t	i;
	t_idx			s_idx;

	i = 1;
	while ((dt->rt_line[idx + i] != '\0')
		&& (ft_iswhite_space(dt->rt_line[idx + i]) == false)
		&& (ft_isalnum_var(dt->rt_line[idx + i]) == true))
		i++;
	s_idx.start = idx + 1;
	s_idx.end = idx + i;
	if (get_substr(&dt->err, &s_tmp.str, dt->rt_line, s_idx) == true)
		return (true);
	if (set_token(dt, s_tmp.str, tk_var, none) == true)
		return (true);
	dt->parse.idx.start = s_idx.end;
	free(s_tmp.str);
	return (false);
}

t_bool	ft_set_tk_var(t_data *dt, register size_t idx)
{
	char			s1[3];
	t_chk_str		chk;

	chk = ft_srchstr(dt->rt_line[idx + 1], MSHL_VAR_SPEC);
	if (chk.ks == true)
	{
		s1[0] = dt->rt_line[idx];
		s1[1] = dt->rt_line[idx +1];
		s1[2] = '\0';
		if (set_token(dt, s1, tk_exp, chk.idx) == true)
			return (true);
		idx ++;
		dt->parse.idx.start = dt->parse.idx.end + 2;
		return (false);
	}
	if (ft_set_tk_var_01(dt, idx) == true)
		return (true);
	return (false);
}
