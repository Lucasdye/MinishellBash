/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:06:09 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:43:44 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_get_exec_var(t_data *dt, char *cmd, char **var)
{
	t_bool	ks;
	char	**arg;

	*var = NULL;
	arg = ft_split_str_wp(cmd);
	if (arg == NULL)
	{
		set_err_std_02(&dt->err);
		return (true);
	}
	cmd = NULL;
	if (set_str_arg(&dt->err, &cmd, arg[0]) == true)
		return (true);
	ks = exec_mini(dt, var, cmd, arg);
	free(cmd);
	free_tab((void *)arg);
	return (ks);
}

static t_bool	ft_extract_home(t_data *dt, char *s_tmp, t_bool ks)
{
	char	**tab;

	if (ks != true)
	{
		tab = ft_split(s_tmp, ':');
		if (tab != NULL)
		{
			if (ft_tablen(tab) > 6)
				ks = set_str_arg(&dt->err, &dt->var.home, tab[5]);
			free_tab((void *)tab);
			return (ks);
		}
	}
	dt->var.home = NULL;
	return (true);
}

t_bool	ft_get_var(t_data *dt)
{
	t_bool	ks;
	char	*s1;
	char	*s_tmp;

	s1 = NULL;
	if (ft_get_exec_var(dt, "hostname -s", &dt->var.hostname) == true)
		return (true);
	if (ft_get_exec_var(dt, "id -u -n", &dt->var.user) == true)
		return (true);
	if (dt->ks_mini == false)
		return (false);
	if (set_str_arg(&dt->err, &s1, MSHL_CMD_HOME) == true)
		return (true);
	s1 = ft_strjoin_m(s1, dt->var.user);
	if (s1 == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	ks = ft_get_exec_var(dt, s1, &s_tmp);
	ft_extract_home(dt, s_tmp, ks);
	free (s1);
	free(s_tmp);
	return (ks);
}
