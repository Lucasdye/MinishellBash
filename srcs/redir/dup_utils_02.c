/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:25:50 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:46:45 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	dup_src_fd(t_data *dt, int *fd, const int src)
{
	*fd = dup(src);
	if (*fd == ERR)
	{
		set_err_var_01(&dt->err, true, NORMAL, errno);
		dt->err.v.str = strerror(errno);
		log_hist_err(&dt->err);
		return (true);
	}
	close(*fd);
	return (false);
}

t_bool	dup_src_fd_noc(t_data *dt, int *fd, const int src)
{
	*fd = dup(src);
	if (*fd == ERR)
	{
		set_err_var_01(&dt->err, true, NORMAL, errno);
		dt->err.v.str = strerror(errno);
		log_hist_err(&dt->err);
		return (true);
	}
	return (false);
}

t_bool	dup2_src_fd(t_data *dt, int *fd, const int src)
{
	if (dup2(*fd, src) == ERR)
	{
		set_err_var_01(&dt->err, true, NORMAL, errno);
		dt->err.v.str = strerror(errno);
		log_hist_err(&dt->err);
		return (true);
	}
	close(*fd);
	return (false);
}

t_bool	dup2_src_fd_noc(t_data *dt, int *fd, const int src)
{
	if (dup2(*fd, src) == ERR)
	{
		set_err_var_01(&dt->err, true, NORMAL, errno);
		dt->err.v.str = strerror(errno);
		log_hist_err(&dt->err);
		return (true);
	}
	return (false);
}
