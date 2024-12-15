/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule_check_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:50:33 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/15 14:05:01 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*case error pipe in first command after ; */
static t_bool	ft_parse_bad_pipe_01(t_data *dt, register size_t i)
{
	if (i != 0)
	{
		if ((dt->parse.tk.tab[i - 1].type == tk_sep)
			&& (dt->parse.tk.tab[i - 1].subtype == c_inst)
			&& (dt->parse.tk.tab[i].type == tk_redir_op)
			&& (dt->parse.tk.tab[i].subtype == redir_pipe))
		{
			ft_set_err_parse_02(dt, true, redir_pipe);
			return (true);
		}
	}
	if (i < dt->parse.tk.nbr - 1)
	{
		if ((dt->parse.tk.tab[i].type == tk_sep)
			&& (dt->parse.tk.tab[i].subtype == c_inst)
			&& (dt->parse.tk.tab[i + 1].type == tk_sep)
			&& (dt->parse.tk.tab[i + 1].subtype == c_inst))
		{
			ft_set_err_parse_01(dt, SEP_INST);
			return (true);
		}
	}
	return (false);
}

/*case error  in first token */
static t_bool	ft_parse_bad_first(t_data *dt)
{
	if (dt->parse.tk.tab == NULL)
		return (true);
	if ((dt->parse.tk.tab[0].type == tk_redir_op)
		&& (dt->parse.tk.tab[0].subtype == redir_pipe))
	{
		ft_set_err_parse_02(dt, true, redir_pipe);
		return (true);
	}
	if ((dt->parse.tk.tab[0].type == tk_sep)
		&& (dt->parse.tk.tab[0].subtype == c_inst))
	{
		ft_set_err_parse_01(dt, SEP_INST);
		return (true);
	}
	if (dt->parse.tk.tab[0].type == tk_file)
	{
		ft_set_err_parse_05(dt, "file");
		return (true);
	}
	return (false);
}

static t_bool	ft_check_unsupported(t_data *dt)
{
	register size_t	i;

	i = 0;
	while (i < dt->parse.tk.nbr)
	{
		if ((dt->parse.tk.tab[i].type == tk_sep)
			&& (dt->parse.stab[dt->parse.tk.tab[i].subtype].ks == false))
		{
			ft_set_err_parse_03(dt, dt->parse.tk.tab[i].subtype);
			return (true);
		}
		else if ((dt->parse.tk.tab[i].type == tk_redir_op)
			&& (dt->parse.tk.tab[i].subtype >= redir_rp))
		{
			ft_set_err_parse_02(dt, false, dt->parse.tk.tab[i].subtype);
			return (true);
		}
		i++;
	}
	return (false);
}

static t_bool	ft_check_rule_loop(t_data *dt, register size_t i)
{
	if (ft_parse_bad_pipe_01(dt, i) == true)
		return (true);
	if (ft_parse_bad_pipe_01(dt, i) == true)
		return (true);
	if (ft_parse_miss_file_02(dt, i) == true)
		return (true);
	if (ft_parse_bad_str(dt, i) == true)
		return (true);
	return (false);
}

t_bool	ft_check_rules(t_data *dt)
{
	register size_t	i;

	i = 0;
	if (ft_check_err_parse(dt) == true)
		return (true);
	if (ft_check_unsupported(dt) == true)
		return (true);
	if (ft_parse_bad_first(dt) == true)
		return (true);
	else
	{
		while (i < dt->parse.tk.nbr)
		{
			if (ft_check_rule_loop(dt, i) == true)
				return (true);
			i++;
		}
	}
	return (false);
}
