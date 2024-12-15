/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_tk_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:52:37 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/25 07:45:33 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static t_bool	prev_var(t_data *dt, char *name)
{
	if ((dt->parse.tk.idx != 0)
		&& (dt->parse.tk.tab[dt->parse.tk.idx].type == tk_file))
	{
		if ((dt->parse.tk.tab[dt->parse.tk.idx - 1].type == tk_redir_op)
			&& (dt->parse.tk.tab[dt->parse.tk.idx - 1].subtype != redir_pipe)
			&& (ft_isvar_str(name) == true))
		{
			if (set_str_arg(&dt->err, &dt->parse.tk.tab[dt->parse.tk.idx].prvar
					, name) == true)
				return (true);
		}
		else
			dt->parse.tk.tab[dt->parse.tk.idx].prvar = NULL;
	}
	else
		dt->parse.tk.tab[dt->parse.tk.idx].prvar = NULL;
	return (false);
}

static t_bool	add_token(t_data *dt, char *name, t_tk_type type
	, size_t subtype)
{
	if (redim_tk_tab(dt, 1) == true)
		return (true);
	if (set_str_arg(&dt->err, &dt->parse.tk.tab[dt->parse.tk.idx].name,
			name) == true)
		return (true);
	dt->parse.tk.tab[dt->parse.tk.idx].type = type;
	dt->parse.tk.tab[dt->parse.tk.idx].subtype = subtype;
	if (prev_var(dt, name) == true)
		return (true);
	dt->parse.tk.idx++;
	dt->parse.tk.nbr++;
	return (false);
}

t_bool	set_token(t_data *dt, char *s1, t_tk_type type, size_t subtype)
{
	if (type == tk_none)
		return (false);
	if (add_token(dt, s1, type, subtype) == true)
		return (true);
	return (false);
}
