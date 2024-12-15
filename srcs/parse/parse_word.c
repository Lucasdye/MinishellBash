/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:36:13 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/18 15:44:47 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_chk_tk_word(t_data *dt, t_str *s_tmp)
{
	char		**arg;

	if (s_tmp == NULL)
	{
		set_err_std_02(&dt->err);
		return (true);
	}
	arg = &dt->parse.tk.tab[dt->parse.icmd.idx].name;
	*arg = ft_strjoin_m(*arg, "\x20");
	if (*arg != NULL)
	{
		*arg = ft_strjoin_m(*arg, s_tmp->str);
		if (*arg != NULL)
		{
			free_tstr(s_tmp);
			return (false);
		}
	}
	free_tstr(s_tmp);
	set_err_std_01(&dt->err);
	return (true);
}
