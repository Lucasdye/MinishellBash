/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:23:08 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:29:18 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_set_white_space_str(t_data *dt, t_exp_var *sd)
{
	t_bool	ks;
	t_idx	idx;

	ks = false;
	idx.start = sd->s.ptr;
	sd->s.ptr = ft_skip_whitespace(sd->s.str, sd->s.ptr);
	idx.end = sd->s.ptr;
	if (get_substr(&dt->err, &sd->s_var.str, sd->s.str, idx) == true)
		return (true);
	sd->s_var.size = idx.end - idx.start;
	ks = ft_strjcat_obj(&sd->s_line, &sd->s_var);
	free_obj(&sd->s_var);
	if (ks == true)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	return (true);
}
