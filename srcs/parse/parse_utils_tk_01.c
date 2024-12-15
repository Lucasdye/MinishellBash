/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_tk_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:33:26 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/28 15:34:21 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	copy_tk_tab(t_token **dest, t_token *src, register size_t size)
{
	register size_t	i;

	i = 0;
	while (i < size)
	{
		(*dest)[i] = src[i];
		i++;
	}
	return (false);
}

static t_bool	redim_core(t_data *dt, size_t new_size)
{
	t_token	*tmp_tab;

	if (init_tk_tab(dt, &tmp_tab, dt->parse.tk.size) == false)
	{
		if (copy_tk_tab(&tmp_tab, dt->parse.tk.tab, dt->parse.tk.size) == false)
		{
			free(dt->parse.tk.tab);
			if (init_tk_tab(dt, &dt->parse.tk.tab, new_size) == false)
			{
				if (copy_tk_tab(&dt->parse.tk.tab, tmp_tab
						, dt->parse.tk.size) == false)
				{
					free(tmp_tab);
					dt->parse.tk.size = new_size;
					return (false);
				}
			}
		}
		free(tmp_tab);
	}
	return (false);
}

t_bool	redim_tk_tab(t_data *dt, register size_t size_data)
{
	t_bool	redim;
	size_t	new_size;

	redim = false;
	new_size = dt->parse.tk.size;
	while ((new_size - dt->parse.tk.idx) <= size_data)
	{
		new_size *= 2;
		redim = true;
	}
	if (redim == true)
	{
		if (redim_core(dt, new_size) == true)
			return (true);
	}
	return (false);
}
