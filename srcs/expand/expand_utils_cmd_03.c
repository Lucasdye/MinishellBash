/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_cmd_03.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:01:36 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/17 13:39:39 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_order_arg_join(t_data *dt, char **s_tmp, t_token tk)
{
	register size_t	i;
	t_bool			ks;

	i = 0;
	ks = false;
	while (tk.arg[i] != NULL)
	{
		if (ft_strjcat(s_tmp, tk.arg[i]) == false)
		{
			*s_tmp = ft_strjoin_m(*s_tmp, "\x20");
			if (s_tmp == NULL)
				ks = true;
		}
		else
			ks = true;
		if (ks == true)
		{
			set_err_std_02(&dt->err);
			return (true);
		}
		i++;
	}
	return (false);
}

static t_bool	ft_order_arg_split(t_data *dt, char *s_tmp, t_token *tk)
{
	t_bool	ks;

	ks = false;
	free_tab((void *)tk->arg);
	tk->arg = ft_split_str_wp(s_tmp);
	if (tk->arg == NULL)
	{
		set_err_std_01(&dt->err);
		ks = true;
	}
	else
	{
		free(tk->name);
		if (set_str_arg(&dt->err, &tk->name, tk->arg[0]) == true)
			ks = true;
	}
	return (ks);
}

t_bool	ft_order_arg_cmd(t_data *dt, register size_t idx)
{
	t_bool	ks;
	char	*s_tmp;

	s_tmp = NULL;
	ks = false;
	if (dt->parse.tk.tab[idx].arg[0] == NULL)
		return (ks);
	if (ft_order_arg_join(dt, &s_tmp, dt->parse.tk.tab[idx]) == true)
		ks = true;
	else
		ks = ft_order_arg_split(dt, s_tmp, &dt->parse.tk.tab[idx]);
	free(s_tmp);
	return (ks);
}
