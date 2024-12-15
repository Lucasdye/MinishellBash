/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:21:50 by lbouguet          #+#    #+#             */
/*   Updated: 2023/11/21 08:24:30 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_her_fds(t_data *dt, t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nb_blocs)
	{
		if (dt->hd.fd[i])
		{	
			close_fd(dt, dt->hd.fd[i]);
		}
		i++;
	}
}

void	close_all_her_fds_but_current(t_data *dt, t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nb_blocs)
	{
		if (dt->hd.fd[i] && i != exec->count_bloc - 1)
		{	
			close_fd(dt, dt->hd.fd[i]);
		}
		i++;
	}
}
