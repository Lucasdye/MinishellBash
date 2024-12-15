/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_print_02.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 09:44:59 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/20 18:51:57 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_is_var_eq( char *s)
{
	register size_t	i;
	t_bool			ks;

	i = 0;
	ks = false;
	while (s[i] != '\0' && ks == false)
	{
		if (s[i] == EQUAL)
			ks = true;
		i++;
	}
	return (ks);
}

static t_bool	ft_rstr_var_01(t_data *dt, char *s, t_dup *s_tmp1
	, t_dup *s_tmp2)
{
	t_bool	ks;

	ks = false;
	s_tmp1->str = ft_strjoin_m(s_tmp1->str, ft_strdup(dt->var.p_prnt));
	if (s_tmp1->str == NULL)
		return (true);
	s_tmp1->size = ft_strlen(s_tmp1->str);
	*s_tmp2 = ft_strdup_obj(s, EQUAL, 0, ft_strlen(s));
	if (s_tmp2->str == NULL)
		return (true);
	ks = ft_strjcat_obj(s_tmp1, s_tmp2);
	return (ks);
}

static t_bool	ft_rstr_var_02(char *s, t_dup *s_tmp1, t_dup *s_tmp2)
{
	t_bool	ks;
	size_t	size;

	ks = false;
	s_tmp1->str = ft_strjoin_m(s_tmp1->str, "=\x22");
	if (s_tmp1->str == NULL)
		return (true);
	s_tmp1->size += 2;
	size = s_tmp2->ptr;
	free_str(&s_tmp2->str);
	*s_tmp2 = ft_dupjoint(s, "\x22", '\0', (size + 1));
	if (s_tmp2->str == NULL)
		return (true);
	ks = ft_strjcat_obj(s_tmp1, s_tmp2);
	free_str(&s_tmp2->str);
	return (ks);
}

static t_bool	ft_rstr_var(t_data *dt, t_err *err, char **s, t_bool ks)
{
	t_dup			s_tmp1;
	t_dup			s_tmp2;

	if (*s == NULL)
		return (true);
	ft_init_t_dup(&s_tmp1);
	ft_init_t_dup(&s_tmp2);
	if (ft_rstr_var_01(dt, *s, &s_tmp1, &s_tmp2) == true)
	{
		free_str(&s_tmp1.str);
		return (true);
	}
	if (ks == true)
	{
		if (ft_rstr_var_02(*s, &s_tmp1, &s_tmp2) == true)
		{
			free_str(&s_tmp1.str);
			return (true);
		}
	}
	free(*s);
	ks = set_str_arg(err, s, s_tmp1.str);
	free_str(&s_tmp1.str);
	free_str(&s_tmp2.str);
	return (ks);
}

t_bool	print_env_filter(t_data *dt, t_err *err, t_env *env, t_bool flt)
{
	register size_t	i;
	t_bool			ks;

	i = 0;
	while (i < env->idx)
	{
		ks = ft_is_var_eq(env->tab[i]);
		if (flt == false)
		{
			if (ft_rstr_var(dt, err, &env->tab[i], ks) == true)
			{
				set_err_std_01(err);
				return (true);
			}
			if (print_env_line(err, env->tab, i) == true)
				return (true);
		}
		else if (ks == true)
		{
			if (print_env_line(err, env->tab, i) == true)
				return (true);
		}
		i++;
	}
	return (false);
}
