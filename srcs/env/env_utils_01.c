/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:35:07 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/16 13:24:34 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static void	set_env_err(t_data *dt, t_bool opt)
{
	if (opt == false)
	{
		set_err_var_01(&dt->err, true, CRITICAL, ENOMEM);
		dt->err.v.str = strerror(ENOMEM);
		set_str_arg(&dt->err, &dt->err.v.arg, "ENV");
	}
	else
	{
		set_err_var_01(&dt->err, false, WARNING, EINVAL);
		dt->err.v.str = MSHL_NO_ENV_ARG;
		set_str_arg(&dt->err, &dt->err.v.arg, "ENV");
	}
	log_hist_err(&dt->err);
}

inline static size_t	count_env(t_data *dt, char **env)
{
	register size_t	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	if (i == 0)
		set_env_err(dt, true);
	return (i);
}

char	*get_env_var(t_data *dt, char *var_name)
{
	t_chk_stab_e	ret;
	register size_t	i;

	i = 0;
	if (!var_name)
		return (NULL);
	ret = chk_var_exist_env(&dt->err, &dt->env, var_name);
	if (ret.ks == true)
		return (NULL);
	else if (ret.stab.ks == true)
	{
		while ((dt->env.tab[ret.stab.idx][i] != '\0')
			&& (dt->env.tab[ret.stab.idx][i] != '='))
			i++;
		return (ft_substr(dt->env.tab[ret.stab.idx], (i + 1)
				, ft_strlen(dt->env.tab[ret.stab.idx])));
	}
	return (ft_strdup("\0"));
}

static t_bool	ft_set_shlvl(t_data *dt)
{
	char	*s1;
	int		count;
	t_bool	ks;

	ks = false;
	dt->ks_mini = false;
	s1 = get_env_var(dt, "SHLVL");
	if (s1 == NULL)
		return (true);
	if (s1[0] == '\0')
		ks = set_env_var(dt, (char *[3]){"SHLVL", "1", NULL});
	else
	{
		count = ft_atoi(s1) + 1;
		free_str(&s1);
		s1 = ft_itoa(count);
		ks = set_env_var(dt, (char *[3]){"SHLVL", s1, NULL});
	}
	free (s1);
	return (ks);
}

t_bool	set_envp(t_data *dt, char **envp)
{
	register size_t	i;

	dt->env.size = count_env(dt, envp);
	dt->env.idx = dt->env.size;
	if (ft_create_stab(&dt->err, &dt->env.tab, dt->env.size) == true)
		return (true);
	i = 0;
	while (envp[i] != NULL)
	{
		if (set_str_arg(&dt->err, &dt->env.tab[i], envp[i]) == true)
		{
			free_envp(dt->env.tab, i);
			return (true);
		}
		i++;
	}
	dt->env.tab[i] = NULL;
	if (dt->env.size == 0)
	{
		if (set_def_env(dt) == true)
			return (true);
	}
	else if (ft_set_shlvl(dt) == true)
		return (true);
	return (false);
}
