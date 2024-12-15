/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule_check_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:52:13 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/15 14:07:42 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*case error pipe in last command after, without command */
t_bool	ft_parse_bad_pipe_02(t_data *dt, register size_t i)
{
	if (i == (dt->parse.tk.nbr - 1))
	{
		if ((dt->parse.tk.tab[i].type == tk_redir_op)
			&& (dt->parse.tk.tab[i].subtype == redir_pipe))
		{
			ft_set_err_parse_02(dt, true, redir_pipe);
			return (true);
		}
	}
	else if (i < (dt->parse.tk.nbr - 1))
	{
		if ((dt->parse.tk.tab[i].type == tk_redir_op)
			&& (dt->parse.tk.tab[i].subtype == redir_pipe)
			&& (dt->parse.tk.tab[i + 1].type == tk_redir_op)
			&& (dt->parse.tk.tab[i + 1].subtype == redir_pipe))
		{
			ft_set_err_parse_02(dt, true, redir_pipe);
			return (true);
		}
	}
	return (false);
}

t_bool	ft_parse_miss_file_01(t_data *dt, register size_t i)
{
	if ((dt->parse.tk.tab[i].type == tk_redir_op)
		&& (dt->parse.rtab[i].flg != NONE))
	{
		if (i == dt->parse.tk.nbr -1)
		{
			ft_set_err_parse_02(dt, true, 0);
			return (true);
		}
		if (dt->parse.tk.tab[i + 1].type != tk_file)
		{
			ft_set_err_parse_05(dt, dt->parse.tk.tab[i + 1].name);
			return (true);
		}
	}
	return (false);
}

t_bool	ft_parse_miss_file_02(t_data *dt, register size_t i)
{
	if ((dt->parse.tk.tab[i].type == tk_redir_op)
		&& (dt->parse.tk.tab[i].subtype != redir_pipe)
		&& (dt->parse.rtab[dt->parse.tk.tab[i].subtype].opt == false))
	{
		if (i == dt->parse.tk.nbr - 1)
		{
			ft_set_err_parse_02(dt, true, 0);
			return (true);
		}
		if (dt->parse.tk.tab[i + 1].type != tk_file)
		{
			ft_set_err_parse_05(dt, dt->parse.tk.tab[i].name);
			return (true);
		}
	}
	return (false);
}
