/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_cmd_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:52:17 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/17 13:39:48 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_exp_core_str(t_data *dt, char **tab_s)
{
	register size_t	i;
	char			**tab_sb;

	i = 0;
	while (tab_s[i] != NULL)
	{
		if (ft_exp_str(dt, &tab_s[i], &tab_sb) == true)
		{
			if (tab_sb != NULL)
				free_tab((void *)tab_sb);
			return (true);
		}
		i++;
		free_tab((void *)tab_sb);
	}
	return (false);
}

static t_bool	ft_exp_core(t_data *dt, char **tab_s, register size_t idx)
{
	t_chk_stab		chk;
	t_bool			ks_cmd;

	ks_cmd = false;
	if ((tab_s[0] != NULL)
		&& (dt->parse.tk.tab[idx].type == tk_cmd)
		&& (tab_s[0][0] == '$'))
		ks_cmd = true;
	if (ft_exp_core_str(dt, tab_s) == true)
	{
		free_tab((void *)tab_s);
		return (true);
	}
	if (ks_cmd == true)
	{
		chk = ft_isstr_ftab_sz(tab_s[0], dt->parse.ftab, MSHL_CMD_B_NUM);
		if (chk.ks == true)
		{
			dt->parse.tk.tab[idx].type = tk_cmd_b;
			dt->parse.tk.tab[idx].subtype = chk.idx;
		}
	}
	return (false);
}

t_bool	ft_expand_cmd(t_data *dt, register size_t idx)
{
	t_bool	ks;
	char	**tab_s;

	ks = false;
	tab_s = ft_split_str_wp(dt->parse.tk.tab[idx].name);
	if (tab_s == NULL)
		return (set_err_std_01(&dt->err), true);
	if (ft_exp_core(dt, tab_s, idx) == true)
	{
		free_tab((void *)tab_s);
		return (true);
	}
	free(dt->parse.tk.tab[idx].name);
	dt->parse.tk.tab[idx].name = NULL;
	ks = set_str_arg(&dt->err, &dt->parse.tk.tab[idx].name, tab_s[0]);
	if (ks == false)
		ks = ft_set_tk_arg_tab(dt, &tab_s, idx);
	free_tab((void *)tab_s);
	return (ks);
}
