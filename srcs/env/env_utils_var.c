/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:24:30 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/16 15:35:39 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	set_var_name(t_err *err, char **dst, char *src)
{
	register size_t	i;

	*dst = NULL;
	i = 0;
	while ((src[i] != '\0') && (src[i] != EQUAL))
		i++;
	*dst = ft_calloc((i + 1), sizeof(char));
	if (*dst == NULL)
	{
		set_err_var_01(err, true, CRITICAL, ENOMEM);
		return (true);
	}
	ft_strlcpy(*dst, src, i);
	return (false);
}

static t_bool	chk_var(char **s1, char **s2, register size_t	idx
	, t_chk_stab_e *chk)
{
	t_bool	ks;

	ks = false;
	chk->ks = false;
	if (ft_strchk(*s1, *s2) == true)
	{
		chk->stab.ks = true;
		chk->stab.idx = idx;
		ks = true;
		free(*s1);
	}
	free(*s2);
	return (ks);
}

t_chk_stab_e	chk_var_exist_env(t_err *err, t_env *env, char *str)
{
	t_chk_stab_e	chk;
	register size_t	i;
	char			*s1;
	char			*s2;

	init_chk_var(&chk);
	i = 0;
	if (set_err_init(err, str) == true)
		return (chk);
	if (env->idx == 0)
		chk.ks = false;
	if (set_var_name(err, &s1, str) == true)
		return (chk);
	while (i < env->idx)
	{
		if (set_var_name(err, &s2, env->tab[i]) == true)
			return (free_str(&s1), chk);
		if (chk_var(&s1, &s2, i, &chk) == true)
			return (chk);
		i++;
	}
	free_str(&s1);
	return (chk);
}
