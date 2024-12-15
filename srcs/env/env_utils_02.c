/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:19:45 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 08:47:38 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	swap_str(t_err *err, char **s1, char **s2)
{
	char	*tmp_str;

	if (set_str_arg(err, &tmp_str, *s1) == true)
		return (true);
	free(*s1);
	if (set_str_arg(err, s1, *s2) == true)
		return (true);
	free(*s2);
	if (set_str_arg(err, s2, tmp_str) == true)
		return (true);
	free(tmp_str);
	return (false);
}

void	sort_env_tab(t_err *err, t_env *env)
{
	register size_t	i;
	register size_t	j;

	i = 0;
	if (!env->size)
		return ;
	while (i < (env->size - 1))
	{
		j = i + 1 ;
		while (j < env->size)
		{
			if (ft_strcmp(env->tab[i], env->tab[j]) > 0)
			{
				if (swap_str(err, &env->tab[i],
						&env->tab[j]) == true)
					return ;
			}
			j++;
		}
		i++;
	}
	return ;
}

void	push_up_env_tab(t_err *err, t_env *env, register size_t idx)
{
	while (idx < env->size - 1)
	{
		if (set_str_arg_builtin(err, &env->tab[idx], env->tab[idx + 1]) == true)
			return ;
		free_str(&env->tab[idx + 1]);
		idx++;
	}
	env->tab[idx] = NULL;
	env->idx -= 1;
	return ;
}
