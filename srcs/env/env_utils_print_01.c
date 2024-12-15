/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_print_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:30:20 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 09:05:16 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	print_env(t_data *dt, char **env, t_bool ks)
{
	register size_t	i;
	char			*str;
	t_bool			ks_w;

	i = 0;
	while (env[i] != NULL)
	{
		str = ft_strjoin(env[i], "\n");
		if (ks == true)
			ks_w = ft_swrite(&dt->err, dt->var.p_prnt, STDOUT_FILENO);
		ks_w = ft_swrite(&dt->err, str, STDOUT_FILENO);
		free(str);
		if (ks_w == true)
			return (true);
		i++;
	}
	return (false);
}

t_bool	print_env_line(t_err *err, char **env, size_t i)
{
	char			*str;
	t_bool			ks;

	if (env[i] != NULL)
	{
		str = ft_strjoin(env[i], "\n");
		if (str == NULL)
		{
			set_err_std_01(err);
			return (true);
		}
		ks = ft_swrite(err, str, STDOUT_FILENO);
		free(str);
		if (ks == true)
			return (true);
	}
	return (false);
}

static t_bool	dup_env_tab(t_data *dt, t_env *env)
{
	register size_t	i;

	i = 0;
	while (i < dt->env.idx)
	{
		if (set_str_arg(&dt->err, &env->tab[i], dt->env.tab[i]) == true)
			return (true);
		i++;
	}
	env->tab[i] = NULL;
	return (false);
}

t_bool	print_env_sort(t_data *dt, t_err *err, t_bool flt)
{
	t_env			env;
	t_bool			ks;

	ks = false;
	env.idx = dt->env.idx;
	env.size = dt->env.idx;
	env.tab = ft_calloc((dt->env.idx + 1), sizeof(*env.tab));
	if (env.tab == NULL)
	{
		set_err_std_01(err);
		return (true);
	}
	if (dup_env_tab(dt, &env) == true)
		return (true);
	if (flt == false)
		sort_env_tab(&dt->err, &env);
	ks = print_env_filter(dt, err, &env, flt);
	free_tab_idx((void *)env.tab, env.size);
	return (ks);
}
