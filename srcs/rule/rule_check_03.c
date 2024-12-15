/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule_check_03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:11:06 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/15 16:16:04 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_parse_bad_str_null(t_data *dt, register size_t i)
{
	if (i == dt->parse.tk.nbr - 1)
		ft_set_err_parse_02(dt, true, 0);
	else if (dt->parse.tk.tab[i + 1].type != tk_file)
		ft_set_err_parse_05(dt, dt->parse.tk.tab[i].name);
	return ;
}

t_bool	ft_parse_bad_str(t_data *dt, register size_t i)
{
	if (i != 0)
	{
		if ((dt->parse.tk.tab[i].type == tk_file)
			&& (dt->parse.tk.tab[i].name == NULL))
		{
			ft_parse_bad_str_null(dt, i);
			return (true);
		}
		if ((dt->parse.tk.tab[i].type == tk_file)
			&& (dt->parse.tk.tab[i].name[0] == '\0')
			&& (dt->parse.tk.tab[i - 1].type == tk_redir_op)
			&& (dt->parse.tk.tab[i].prvar != NULL))
		{
			ft_set_err_parse_04(dt, dt->parse.tk.tab[i].prvar);
			return (true);
		}
	}
	return (false);
}

static t_bool	ft_chk_redir(t_data *dt, register size_t i)
{
	register t_redir_op	n_redir;

	n_redir = none;
	if (dt->parse.tk.tab[i + 1].subtype == redir_l)
		n_redir = redir_l;
	else if (dt->parse.tk.tab[i + 1].subtype == redir_inp)
		n_redir = redir_inp;
	else if (dt->parse.tk.tab[i + 1].subtype == redir_pipe)
		n_redir = redir_pipe;
	if (n_redir != none)
	{
		ft_set_err_parse_01(dt, n_redir);
		return (true);
	}
	return (false);
}

t_bool	ft_parse_bad_03(t_data *dt, register size_t	i, t_redir_op n_rp)
{
	register t_bool		ks;

	ks = ((dt->parse.tk.tab[i].type == tk_redir_op)
			&& (dt->parse.tk.tab[i].subtype == n_rp));
	if ((ks == true) && (dt->parse.tk.tab[i + 1].type == tk_redir_op))
	{
		if (ft_chk_redir(dt, i) == true)
			return (true);
	}
	else if ((ks == true) && (i == (dt->parse.tk.nbr - 1)))
	{
		ft_set_err_parse_02(dt, true, none);
		return (true);
	}
	return (false);
}

t_bool	ft_check_err_parse(t_data *dt)
{
	if (dt->parse.err_space == true)
	{
		set_err_var_01(&dt->err, true, NORMAL, 2);
		dt->err.v.str = MSHL_PARSE_BAD_TOKEN ;
		set_str_arg(&dt->err, &dt->err.v.arg, MSHL_PARSE_BAD_SPACE);
		log_hist_err(&dt->err);
		return (true);
	}
	return (false);
}
