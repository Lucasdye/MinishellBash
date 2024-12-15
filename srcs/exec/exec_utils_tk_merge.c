/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_tk_merge.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:17:22 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/18 19:38:35 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static void	push_up_tab(t_data *dt, register size_t idx)
{
	register size_t	j;

	j = 0;
	while ((j + idx) < dt->parse.tk.nbr)
	{
		dt->parse.tk.tab[j + idx] = dt->parse.tk.tab[j + idx + 1];
		j++;
	}
	dt->parse.tk.nbr--;
	dt->parse.tk.idx--;
	return ;
}

inline static t_bool	ft_move_line(t_data *dt, register size_t i)
{
	if (set_str_arg(&dt->err, &dt->parse.tk.tab[i -1].prvar
			, dt->parse.tk.tab[i].prvar) == true)
		return (true);
	free_tk_u(&dt->parse.tk.tab, i);
	push_up_tab(dt, i);
	return (false);
}

t_bool	ft_merge_tk_redir(t_data *dt)
{
	register size_t	i;

	i = 1 ;
	while (i < (dt->parse.tk.nbr))
	{
		if ((dt->parse.tk.tab[i].type == tk_file)
			&& (dt->parse.tk.tab[i - 1].type == tk_redir_op)
			&& (dt->parse.tk.tab[i - 1].subtype != redir_pipe)
			&& (dt->parse.rtab[dt->parse.tk.tab[i - 1].subtype].opt == false))
		{
			free(dt->parse.tk.tab[i - 1].arg[1]);
			if (set_str_arg(&dt->err, &dt->parse.tk.tab[i -1].arg[1]
					, dt->parse.tk.tab[i].name) == true)
				return (true);
			if (dt->parse.tk.tab[i].prvar != NULL)
			{
				if (ft_move_line(dt, i) == true)
					return (true);
			}
		}
		i++;
	}
	return (false);
}
