/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_var_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:18:00 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:30:58 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_set_def_str(t_data *dt, t_exp_var *sd)
{
	t_bool	ks;

	if (ft_var_read_line(sd, &sd->s_var, &sd->s) == true)
	{
		if (errno != 0)
			set_err_std_01(&dt->err);
		else
			set_err_std_02(&dt->err);
		return (true);
	}
	ks = ft_strjcat_obj(&sd->s_line, &sd->s_var);
	free_obj(&sd->s_var);
	if (ks == true)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	return (false);
}

inline static t_bool	ft_case_other(t_data *dt, t_exp_var *sd)
{
	if (ft_isdigit(sd->s.str[sd->s.ptr + 1]) == true)
	{
		sd->s.ptr++;
		while (ft_isdigit(sd->s.str[sd->s.ptr]) == true)
			sd->s.ptr++;
	}
	else
	{
		sd->s.ptr++;
		sd->s_tmp = ft_var_dup(sd->s.str, sd->s.ptr, sd->s.size);
		if (sd->s_tmp.str == NULL)
			return (set_err_std_01(&dt->err), true);
		sd->s.ptr = sd->s_tmp.ptr;
		sd->s_var.str = get_env_var(dt, sd->s_tmp.str);
		if (sd->s_var.str == NULL)
			return (set_err_std_01(&dt->err), true);
		sd->s_var.ptr = 0;
		sd->s_var.size = ft_strlen(sd->s_var.str);
	}
	return (false);
}

static t_bool	ft_set_var_str_01(t_data *dt, t_exp_var *sd)
{
	t_chk_str		chk;

	chk = ft_srchstr(sd->s.str[sd->s.ptr + 1], MSHL_VAR_SPEC);
	if (chk.ks == true)
	{
		if (MSHL_VAR_SPEC[chk.idx] == '?')
		{
			if (ft_expand_exitcode(dt, &sd->s_var.str) == true)
				return (true);
			sd->s_var.size = ft_strlen(sd->s_var.str);
		}
		sd->s.ptr += 2;
	}
	else if ((sd->s.str[sd->s.ptr + 1] == '\0')
		|| (ft_iswhite_space(sd->s.str[sd->s.ptr + 1]) == true))
	{
		if (set_str_arg(&dt->err, &sd->s_var.str, "$") == true)
			return (true);
		sd->s_var.size = 1;
		sd->s.ptr++;
	}
	else if (ft_case_other(dt, sd) == true)
		return (true);
	return (false);
}

t_bool	ft_var_read(t_data *dt, char **s1)
{
	t_exp_var		sd;

	init_exp_data(&sd);
	sd.s.size = ft_strlen(*s1);
	if (set_str_arg(&dt->err, &sd.s.str, *s1) == true)
		return (true);
	free(*s1);
	*s1 = NULL;
	while ((sd.ks_end_s == false) && (sd.ks == false))
	{
		if (ft_set_def_str(dt, &sd) == true)
			return (free_all_obj(&sd), true);
		free_obj(&sd.s_tmp);
		if (sd.ks_ls == true)
		{
			if (ft_set_var_str_01(dt, &sd) == true)
				return (free_all_obj(&sd), true);
			sd.ks = ft_strjcat_obj(&sd.s_line, &sd.s_var);
			free_obj(&sd.s_var);
			sd.ks_ls = false;
		}
	}
	if (set_str_arg(&dt->err, s1, sd.s_line.str) == true)
		sd.ks = true;
	return (free_all_obj(&sd), sd.ks);
}
