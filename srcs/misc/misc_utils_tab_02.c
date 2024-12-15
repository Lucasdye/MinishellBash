/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_tab_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:23:35 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:34:34 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_create_stab(t_err *err, char ***tab, size_t size)
{
	if (*tab == NULL)
	{
		*tab = ft_calloc((size +1), sizeof(char *));
		if (*tab == NULL)
		{
			set_err_std_01(err);
			return (true);
		}
	}
	return (false);
}

t_bool	ft_copy_stab(t_err *err, char ***dest, char **src
	, register size_t size)
{
	register size_t	i;

	i = 0;
	while (i < size)
	{
		if (set_str_arg_builtin(err, &(*dest)[i], src[i]) == true)
		{
			free_tab_idx((void *)dest, i);
			return (true);
		}
		i++;
	}
	(*dest)[i] = NULL;
	return (false);
}

t_bool	ft_resize_stab(t_err *err, char ***tab, register size_t size
	, register size_t new_size)
{
	char	**tmp_tab;

	if (ft_create_stab(err, &tmp_tab, size) == false)
	{
		if (ft_copy_stab(err, &tmp_tab, *tab, size) == false)
		{
			free_tab((void *)tab);
			if (ft_create_stab(err, tab, new_size) == false)
			{
				if (ft_copy_stab(err, tab, tmp_tab, size) == false)
				{
					free_tab((void *)tmp_tab);
					return (false);
				}
			}
		}
		free_tab((void *)tmp_tab);
	}
	return (true);
}
