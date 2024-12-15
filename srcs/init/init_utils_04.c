/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_04.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:35:20 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/10 20:27:25 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_struct_hd_exec(t_data *dt)
{
	dt->hd.eof = NULL;
	dt->hd.isquote = false;
	dt->hd.pipe.fd[0] = 0;
	dt->hd.pipe.fd[1] = 1;
	dt->hd.idx = 0;
	return ;
}

t_bool	ft_init_tab_hd_fd(t_data *dt)
{
	dt->hd.fd = ft_calloc(dt->parse.nbr_bk, sizeof(int));
	if (dt->hd.fd == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}	
	return (false);
}
