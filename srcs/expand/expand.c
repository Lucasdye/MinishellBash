/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:26:23 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/17 13:40:00 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_exp_core_var(t_data *dt, char **s1)
{
	char	**tab_sb;
	t_bool	ks;

	ks = ft_exp_str(dt, s1, &tab_sb);
	if (tab_sb != NULL)
		free_tab((void *)tab_sb);
	return (ks);
}

inline static t_bool	ft_exp_part(t_data *dt, register size_t i)
{
	if ((dt->parse.tk.tab[i].type == tk_cmd)
		|| (dt->parse.tk.tab[i].type == tk_cmd_b))
	{
		if (ft_expand_cmd(dt, i) == true)
			return (true);
	}
	else if (dt->parse.tk.tab[i].type == tk_redir_op)
	{
		if ((ft_expand_arg_redir(dt, &dt->parse.tk.tab[i]) == true)
			&& (dt->parse.rtab[dt->parse.tk.tab[i].subtype].opt == true))
			return (true);
	}
	return (false);
}

inline static t_bool	chk_file_exp(t_data *dt, register size_t i)
{
	if (i == 0)
		return (true);
	else if ((dt->parse.tk.tab[i - 1].type == tk_redir_op)
		&& ((dt->parse.tk.tab[i - 1].subtype != redir_inp)
			&& (dt->parse.tk.tab[i - 1].subtype != redir_s_inp)))
		return (true);
	return (false);
}

t_bool	ft_expand(t_data *dt)
{
	register size_t	i;

	i = 0;
	if (ft_init_tab_hd_fd(dt) == true)
		return (true);
	while (i < dt->parse.tk.idx)
	{
		if ((dt->parse.tk.tab[i].type == tk_word)
			|| (dt->parse.tk.tab[i].type == tk_file))
		{
			if (chk_file_exp(dt, i) == true)
			{
				if (ft_exp_core_var(dt, &dt->parse.tk.tab[i].name) == true)
					return (true);
			}
		}
		if (ft_exp_part(dt, i) == true)
			return (true);
		i++;
	}
	return (false);
}
