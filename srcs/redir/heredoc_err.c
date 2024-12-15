/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:55:30 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 07:59:12 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_err_doc(t_data *dt, int fd)
{
	dup_src_fd(dt, &fd, STDIN_FILENO);
	ft_init_sig(false, false);
	close_fd(dt, fd);
	write(STDOUT_FILENO, "\n", 1);
	g_status = 130;
	return ;
}

void	set_err_eof(t_data *dt)
{
	set_err_var_01(&dt->err, true, CRITICAL, 22);
	dt->err.v.str = MSHL_NULL_PARA;
	log_hist_err(&dt->err);
	return ;
}

void	print_err_doc_exit(char *eof)
{
	write(STDERR_FILENO, MSHL_HER_CTRLD_01, ft_strlen(MSHL_HER_CTRLD_01));
	write(STDERR_FILENO, eof, ft_strlen(eof));
	write(STDERR_FILENO, MSHL_HER_CTRLD_02, ft_strlen(MSHL_HER_CTRLD_02));
	write(STDERR_FILENO, "\n", 1);
	return ;
}
