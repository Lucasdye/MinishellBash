/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:44:30 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/14 19:29:48 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_chk(t_chk_str_e *chk)
{
	chk->ks = false;
	chk->s.ks = false;
	chk->s.idx = 0;
	return ;
}

t_chk_str_e	ft_is_redir_str(t_data *dt, size_t idx)
{
	register size_t	i;
	t_chk_str_e		chk;
	t_idx			s_idx;

	ft_init_chk(&chk);
	s_idx.start = idx;
	i = 0;
	while (i < MSHL_REDIR_NUM)
	{
		s_idx.end = idx + dt->parse.rtab[i].size;
		if (get_substr(&dt->err, &dt->tmp.str, dt->rt_line, s_idx) == true)
		{
			chk.ks = true;
			break ;
		}
		if (ft_strchk(dt->parse.rtab[i].str, dt->tmp.str) == true)
		{
			chk.s.ks = true;
			chk.s.idx = i;
		}
		i++;
		free_str(&dt->tmp.str);
	}
	return (chk);
}
