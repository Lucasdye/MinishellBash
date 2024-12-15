/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_setvar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:21:29 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:17:13 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_env_tab_join(t_err *err, char **var_name)
{
	char	*s1;
	char	*s2;

	if (var_name[1] == NULL)
	{
		if (set_str_arg(err, &s2, var_name[0]) == true)
			return (NULL);
		return (s2);
	}
	s1 = ft_strjoin(var_name[0], "=");
	if (s1 == NULL)
	{
		set_err_std_01(err);
		return (NULL);
	}
	s2 = ft_strjoin(s1, var_name[1]);
	if (s2 == NULL)
		set_err_std_01(err);
	free(s1);
	return (s2);
}

inline static t_bool	ft_chk_resize(t_data *dt, char **s_tmp)
{
	t_bool	ks;

	ks = false;
	if (dt->env.idx == dt->env.size)
	{
		ks = resize_env_tab(&dt->err, &dt->env, (dt->env.size + 1));
		if (ks == false)
		{
			ks = set_str_arg_builtin(&dt->err, &dt->env.tab[dt->env.idx],
					*s_tmp);
			dt->env.idx++;
			dt->env.tab[dt->env.idx] = NULL;
		}
	}
	return (ks);
}

static t_bool	ft_set_var(t_data *dt, char **s_tmp, char *arg)
{
	t_chk_stab_e	chk;
	t_bool			ks;

	ks = false;
	chk = chk_var_exist_env(&dt->err, &dt->env, arg);
	if (chk.ks == true)
	{
		ks = true;
	}
	else if (chk.stab.ks == true)
	{
		free(dt->env.tab[chk.stab.idx]);
		ks = set_str_arg_builtin(&dt->err, &dt->env.tab[chk.stab.idx], *s_tmp);
	}
	else
		ks = ft_chk_resize(dt, s_tmp);
	free(*s_tmp);
	return (ks);
}

t_bool	set_env_var(t_data *dt, char **var_name)
{
	char	*s_tmp;
	t_bool	ks;

	ks = false;
	if ((var_name == NULL) || (var_name[0] == NULL)
		|| ((var_name[0] != NULL) && ((var_name[0][0] == '\0')
			|| (ft_isdigit(var_name[0][0]) == true))))
		return (true);
	s_tmp = ft_env_tab_join(&dt->err, var_name);
	if (s_tmp == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	ks = ft_set_var(dt, &s_tmp, var_name[0]);
	return (ks);
}
