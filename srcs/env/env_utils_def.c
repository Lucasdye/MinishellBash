/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_def.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:57:46 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/24 10:01:27 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	set_str(t_data *dt, char *s1)
{
	register size_t	i;

	i = 0;
	if (s1 == NULL)
	{
		set_err_std_02(&dt->err);
		return (true);
	}
	while (s1[i] != '\0' && s1[i] != '=')
		i++;
	i ++;
	s1 = ft_substr(s1, i, ft_strlen(s1) - i);
	if (s1 == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	if (ft_clean_str_quote_ext(dt, &s1).ks == true)
		return (true);
	if (set_env_var(dt, (char *[3]){"PATH", s1, NULL}) == true)
		return (true);
	return (false);
}

static t_bool	set_def_path(t_data *dt)
{
	t_bool	ks;
	int		fd;
	char	*s1;

	if (file_ops(dt, MSHL_DEF_ENV_PATH, &fd, READ) == true)
		return (true);
	s1 = get_next_line(fd);
	if (s1 != NULL)
		ks = set_str(dt, s1);
	while (s1 != NULL)
	{
		free(s1);
		s1 = get_next_line(fd);
	}
	return (ks);
}

static t_bool	set_def_pdw(t_data *dt)
{
	char	*s1;
	t_bool	ks;

	s1 = getcwd(NULL, 0);
	if (s1 == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	ks = set_env_var(dt, (char *[3]){"PWD", s1, NULL});
	free(s1);
	return (ks);
}

t_bool	set_def_env(t_data *dt)
{
	t_bool	ks;

	dt->ks_mini = true;
	if (set_env_var(dt, (char *[2]){"OLDPWD", NULL}) == true)
	{
		return (true);
	}
	if (dt->var.p_type == p_deflt)
	{
		if (set_def_path(dt) == true)
			return (true);
	}
	if (set_def_pdw(dt) == true)
		return (true);
	ks = set_env_var(dt, (char *[3]){"SHLVL", "1", NULL});
	return (ks);
}
