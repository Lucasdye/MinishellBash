/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:43:24 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 16:28:34 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_hd_next_bk(t_data *dt, register size_t	idx)
{
	if (dt->parse.tk.tab[idx].subtype == redir_pipe)
	{
		dt->hd.idx++;
		dt->hd.enc_hd = false;
		dt->hd.pipe.fd[0] = 0;
	}
	return ;
}

t_bool	exec_redir_hd(t_data *dt)
{
	register size_t	i;
	t_bool			ks;

	ks = false;
	dt->hd.enc_hd = 0;
	dt->hd.ks_sigc_her = false;
	i = 0 ;
	while (i < dt->parse.tk.nbr && dt->hd.ks_sigc_her == false)
	{
		if (dt->parse.tk.tab[i].type == tk_redir_op)
		{
			if ((dt->parse.tk.tab[i].subtype == redir_inp)
				|| (dt->parse.tk.tab[i].subtype == redir_s_inp))
			{
				if (ft_set_heredoc(dt, i) == true)
					return (true);
			}
			set_hd_next_bk(dt, i);
		}
		i++;
	}
	return (ks);
}
