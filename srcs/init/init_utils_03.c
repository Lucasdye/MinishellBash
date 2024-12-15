/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 08:45:00 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/28 15:33:09 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_tk_tab_sep(t_data *dt)
{
	dt->parse.stab[c_none].str = "";
	dt->parse.stab[c_none].ks = true;
	dt->parse.stab[c_inst].str = ";";
	dt->parse.stab[c_inst].ks = false;
	dt->parse.stab[c_lbrace].str = "(";
	dt->parse.stab[c_lbrace].ks = false;
	dt->parse.stab[c_rbrace].str = ")";
	dt->parse.stab[c_rbrace].ks = false;
	dt->parse.stab[c_equal].str = "&";
	dt->parse.stab[c_equal].ks = false;
	dt->parse.stab[c_and].str = "&&";
	dt->parse.stab[c_and].ks = false;
	dt->parse.stab[c_or].str = "||";
	dt->parse.stab[c_or].ks = false;
	return ;
}

void	init_exp_data(t_exp_var *sd)
{
	sd->ks = false;
	sd->ks_end_s = false;
	sd->ks_ls = false;
	sd->s.str = NULL;
	sd->s.ptr = 0;
	sd->s_line.str = NULL;
	sd->s_line.ptr = 0;
	sd->s_line.size = 0;
	sd->s_var.str = NULL;
	sd->s_var.ptr = 0;
	sd->s_var.size = 0;
	sd->s_tmp.str = NULL;
	sd->s_tmp.ptr = 0;
	sd->s_tmp.size = 0;
	return ;
}

t_bool	init_tk_tab(t_data *dt, t_token **tab, register size_t size)
{
	*tab = ft_calloc(size, (sizeof(t_token) + 1));
	if (*tab == NULL)
	{
		set_err_var_01(&dt->err, true, FATAL, errno);
		dt->err.v.str = strerror(errno);
		log_hist_err(&dt->err);
		return (true);
	}
	return (false);
}

t_bool	init_t_bk(t_data *dt, size_t idx)
{
	register size_t	i;

	dt->bk.pipe = ft_calloc((idx - 1), sizeof(t_pipe));
	if (dt->bk.pipe == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	i = 0;
	while (i < idx - 1)
	{
		dt->bk.pipe[i].fd[0] = 0;
		dt->bk.pipe[i].fd[1] = 0;
		i++;
	}
	dt->bk.pid = ft_calloc(idx, sizeof(int));
	if (dt->bk.pid == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	dt->bk.ks = false;
	return (false);
}
