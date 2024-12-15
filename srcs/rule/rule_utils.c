/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:53:34 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/15 16:06:22 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*set error firt token other*/
void	ft_set_err_parse_01(t_data *dt, char s1)
{
	char	str_err[2];

	str_err[0] = s1;
	str_err[1] = '\0';
	set_err_var_01(&dt->err, true, NORMAL, 2);
	dt->err.v.str = MSHL_PARSE_BAD_TOKEN;
	set_str_arg(&dt->err, &dt->err.v.arg, str_err);
	log_hist_err(&dt->err);
	return ;
}

/*set error redir */
void	ft_set_err_parse_02(t_data *dt, t_bool opt, t_redir_op n_redir)
{
	if (opt)
		dt->err.v.str = MSHL_PARSE_BAD_TOKEN;
	else
		dt->err.v.str = MSHL_NOT_YET_FUNC;
	set_err_var_01(&dt->err, true, NORMAL, 2);
	if (n_redir != 0)
		set_str_arg(&dt->err, &dt->err.v.arg, dt->parse.rtab[n_redir].str);
	else
		set_str_arg(&dt->err, &dt->err.v.arg, MSHL_DLG_PARSE_NL);
	log_hist_err(&dt->err);
	return ;
}

void	ft_set_err_parse_03(t_data *dt, t_sep_op n_sep)
{
	set_err_var_01(&dt->err, true, NORMAL, 2);
	dt->err.v.str = MSHL_NOT_YET_FUNC;
	set_str_arg(&dt->err, &dt->err.v.arg, dt->parse.stab[n_sep].str);
	log_hist_err(&dt->err);
	return ;
}

void	ft_set_err_parse_04(t_data *dt, char *prev)
{
	set_err_var_01(&dt->err, true, NORMAL, 2);
	dt->err.v.str = MSHL_PARSE_AMB_REDIR;
	set_str_arg(&dt->err, &dt->err.v.arg, prev);
	log_hist_err(&dt->err);
	return ;
}

void	ft_set_err_parse_05(t_data *dt, char *s1)
{
	if (s1 == NULL)
		s1 = "\0";
	set_err_var_01(&dt->err, true, NORMAL, 2);
	dt->err.v.str = MSHL_PARSE_BAD_TOKEN;
	set_str_arg(&dt->err, &dt->err.v.arg, s1);
	log_hist_err(&dt->err);
	return ;
}
