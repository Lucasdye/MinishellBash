/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:37:31 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 09:35:13 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	backup_std(t_data *dt)
{
	if (dup_src_fd(dt, &dt->var.fd.in, STDIN_FILENO) == true)
		return (true);
	if (dup_src_fd(dt, &dt->var.fd.out, STDOUT_FILENO) == true)
		return (true);
	return (false);
}

t_bool	restore_std(t_data *dt)
{
	if (dup2_src_fd(dt, &dt->var.fd.in, STDIN_FILENO) == true)
		return (true);
	if (dup2_src_fd(dt, &dt->var.fd.out, STDOUT_FILENO) == true)
		return (true);
	return (false);
}
