/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:16:49 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/25 08:11:14 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipe(t_data *dt, size_t idx)
{
	register size_t	i;
	register int	j;

	i = 0;
	while (i < idx)
	{
		j = 0;
		while (j < 2)
		{
			if (close(dt->bk.pipe[i].fd[j]) == ERR)
			{
				set_err_std_01(&dt->err);
				return ;
			}
			j++;
		}
		i++;
	}
	return ;
}

t_bool	create_pipe_u(t_data *dt, size_t idx)
{
	if (pipe(dt->bk.pipe[idx].fd) == ERR)
	{
		set_err_std_01(&dt->err);
		return (true);
		close_pipe (dt, idx - 1);
	}
	return (false);
}

t_bool	create_t_pipe(t_data *dt, t_pipe *p)
{
	if (pipe(p->fd) == ERR)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	return (false);
}
