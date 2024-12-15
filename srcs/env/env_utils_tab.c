/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:09:51 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/16 13:10:12 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	create_tab(t_err *err, char ***tab, register size_t size)
{
	*tab = ft_calloc((size + 1), sizeof(char *));
	if (*tab == NULL)
	{
		set_err_var_01(err, true, FATAL, ENOMEM);
		err->v.str = "TAB ENV";
		return (true);
	}
	return (false);
}

static t_bool	copy_tab(t_err *err, char ***dest, char **src
	, register size_t size)
{
	register size_t	i;

	i = 0;
	while (i < size)
	{
		if (set_str_arg_builtin(err, &(*dest)[i], src[i]) == true)
		{
			free_envp(*dest, i);
			return (true);
		}
		i++;
	}
	(*dest)[i] = NULL;
	return (false);
}

t_bool	resize_env_tab(t_err *err, t_env *env, register size_t new_size)
{
	char	**tmp_tab;

	if (create_tab(err, &tmp_tab, env->size) == false)
	{
		if (copy_tab(err, &tmp_tab, env->tab, env->size) == false)
		{
			free_envp(env->tab, env->size);
			if (create_tab(err, &env->tab, new_size) == false)
			{
				if (copy_tab(err, &env->tab, tmp_tab, env->size) == false)
				{
					free_envp(tmp_tab, env->size);
					env->size = new_size;
					return (false);
				}
			}
		}
		free_envp(tmp_tab, env->size);
	}
	return (true);
}
