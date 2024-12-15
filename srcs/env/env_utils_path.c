/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:16:39 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/17 21:19:38 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static void	get_path_err(t_data *dt, int opt)
{
	if (opt == 0)
		set_err_var_01(&dt->err, true, WARNING, ENOMEM);
	else
	{
		set_err_var_01(&dt->err, false, INFO, EINVAL);
		dt->err.v.str = MSHL_NO_ENV_VAR;
		set_str_arg(&dt->err, &dt->err.v.arg, "PATH");
	}
	dt->var.ks_err_path = true;
	log_hist_err_01(dt);
	return ;
}

inline static t_bool	extract_path(t_data *dt, char *s_path)
{
	if (SPTH_MODE == true)
	{
		if (dt->var.path != NULL)
		{
			free_tab((void *)dt->var.path);
			dt->var.path = NULL;
		}
	}
	dt->var.path = ft_split(s_path, ':');
	if (dt->var.path == NULL)
	{
		get_path_err(dt, 0);
		return (true);
	}
	dt->var.ks_err_path = false;
	free(s_path);
	return (false);
}

t_bool	get_path(t_data *dt)
{
	register size_t	i;
	char			*s_path;

	i = 0;
	if ((SPTH_MODE == false) && (dt->var.path != NULL))
	{
		free_tab((void *)dt->var.path);
		dt->var.path = NULL;
	}
	while (i < dt->env.idx)
	{
		if (chk_strstr(dt->env.tab[i], "PATH="))
		{
			s_path = ft_strtrim(dt->env.tab[i], "PATH=");
			if (s_path != NULL)
				return (extract_path(dt, s_path));
			else
				get_path_err(dt, 0);
			return (true);
		}
		i++;
	}
	get_path_err(dt, 1);
	return (false);
}
