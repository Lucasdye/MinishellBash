/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:04:29 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/10 20:25:02 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_shell(t_tk_tab *tk, t_exec *exec)
{
	set_idx_to_cmd(tk, exec);
	if (tk->tab[exec->idx].type == tk_cmd_b)
		return (true);
	return (false);
}

t_bool	is_bin(t_tk_tab *tk, t_exec *exec)
{
	set_idx_to_cmd(tk, exec);
	if (tk->tab[exec->idx].type == tk_cmd)
		return (true);
	else
		return (false);
}

t_bool	is_pipe(t_tk_tab *tk)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < (int)tk->idx)
	{
		if (tk->tab[i].type == tk_redir_op && tk->tab[i].subtype == redir_pipe)
			flag++;
		i++;
	}
	if (flag)
		return (true);
	else
		return (false);
}
