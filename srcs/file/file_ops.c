/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:20:39 by lbouguet          #+#    #+#             */
/*   Updated: 2023/11/21 07:44:45 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_file_err_01(t_data *dt)
{
	set_err_var_01(&dt->err, false, WARNING, 22);
	dt->err.v.str = MSHL_DEF_ARG_NOP;
	log_hist_err(&dt->err);
	return ;
}

static t_bool	set_file_err_02(t_data *dt, char *s1)
{
	char	*s2;

	s2 = NULL;
	set_err_var_01(&dt->err, true, CRITICAL, errno);
	set_str_arg(&dt->err, &dt->err.v.arg, s1);
	set_str_arg(&dt->err, &s2, ": ");
	ft_strjcat(&dt->err.v.arg, s2);
	free_str(&s2);
	set_str_arg(&dt->err, &s2, strerror(errno));
	ft_strjcat(&dt->err.v.arg, s2);
	free(s2);
	log_hist_err(&dt->err);
	return (true);
}

t_bool	file_ops(t_data *dt, const char *pathname, int *fd, t_flag action)
{
	t_bool	ks;

	ks = false;
	if (action == READ)
		*fd = open(pathname, O_RDONLY, 0644);
	else if (action == WRITE)
		*fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (action == APPEND)
		*fd = open(pathname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (action == TRUNC)
		*fd = open(pathname, O_TRUNC, 0644);
	else if (action == CLOSE)
	{
		ks = close_fd(dt, *fd);
		return (ks);
	}
	else
	{
		set_file_err_01(dt);
		return (true);
	}
	if (*fd == ERR)
		ks = set_file_err_02(dt, (char *)pathname);
	return (ks);
}	
