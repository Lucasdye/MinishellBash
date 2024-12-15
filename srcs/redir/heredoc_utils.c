/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:00:10 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 15:09:51 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fd_hd(t_data *dt, t_pipe p)
{
	close_fd(dt, p.fd[0]);
	close_fd(dt, p.fd[1]);
	return ;
}

void	close_fd_hd_tab(t_data *dt)
{
	register size_t	i;

	i = 0;
	while ((i < dt->parse.nbr_bk) && (dt->hd.fd[i]))
	{
		if (dt->hd.fd[i] != 0)
			close_fd(dt, dt->hd.fd[i]);
		i++;
	}
	return ;
}

t_bool	ft_here_pipe(t_data *dt)
{
	if (dt->hd.pipe.fd[0])
	{
		if (close_fd(dt, dt->hd.pipe.fd[0]) == true)
			return (true);
	}
	if (create_t_pipe(dt, &dt->hd.pipe) == true)
		return (true);
	return (false);
}

t_bool	chk_eof(t_data *dt, char *eof)
{
	t_chk_str_e		chk;
	t_quote			qt;
	t_bool			ks;

	if (eof != NULL)
	{
		chk = ft_chk_str_quote_01(eof);
		if (chk.ks != true)
		{
			if (chk.s.ks == true)
			{
				dt->hd.isquote = true;
				ft_init_flg_quote(&qt);
				ks = ft_clean_str_quote(dt, &qt, &eof);
				return (ks);
			}
			return (false);
		}
	}
	set_err_eof(dt);
	return (true);
}
