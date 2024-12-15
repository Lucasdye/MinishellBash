/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_cmd_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:18:05 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:29:48 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static t_bool	ft_set_mem_arg(t_data *dt, register size_t	size
	, int offset, register size_t idx)
{
	dt->parse.tk.tab[idx].arg = ft_calloc((size + 1 - offset), sizeof(char *));
	if (dt->parse.tk.tab[idx].arg == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	return (false);
}

t_bool	ft_set_tk_arg_tab(t_data *dt, char ***tab_s
	, register size_t idx)
{
	register size_t	i;
	register size_t	size;
	int				offset;

	i = 0;
	size = 0;
	offset = 0;
	if (tab_s == NULL)
		return (true);
	while ((*tab_s)[size] != NULL)
		size++;
	if (dt->parse.tk.tab[idx].type == tk_cmd_b)
		offset = 1;
	if (ft_set_mem_arg(dt, size, offset, idx) == true)
		return (true);
	while ((i + offset) < size)
	{
		if (set_str_arg(&dt->err, &dt->parse.tk.tab[idx].arg[i]
				, (*tab_s)[i + offset]) == true)
			return (true);
		i++;
	}
	dt->parse.tk.tab[idx].arg[i] = NULL;
	return (false);
}

static t_bool	ft_isexp_path(char *s)
{
	if ((s[0] != '\0') && (((s[0] == '~') && (s[1] == '/'))
			|| ((s[0] == '~') && (s[1] == '+') && (s[2] == '/'))))
		return (true);
	return (false);
}

inline static t_bool	ft_all_case(t_data *dt, char **arg, register size_t j)
{
	t_chk_str_e		chk;

	chk = ft_clean_str_quote_ext(dt, arg);
	if (chk.ks == true)
		return (true);
	if (chk.s.ks == false)
	{
		if ((j == 0) && (ft_isexp_path(*arg) == true))
		{
			if (ft_expand_path_01(dt, arg, 2) == true)
				return (true);
		}
		else if (ft_var_read(dt, arg) == true)
			return (true);
	}
	else if ((chk.s.ks == true) && (chk.s.idx == true))
	{
		if (ft_var_read(dt, arg) == true)
			return (true);
	}
	return (false);
}

t_bool	ft_exp_str(t_data *dt, char **str, char ***tab_sb)
{
	register size_t	j;

	j = 0;
	*tab_sb = ft_split_str_qt(*str);
	if (*tab_sb == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	free(*str);
	*str = NULL;
	while ((*tab_sb)[j] != NULL)
	{
		if (ft_all_case(dt, &(*tab_sb)[j], j) == true)
			return (true);
		if (ft_strjcat(str, (*tab_sb)[j]) == true)
		{
			set_err_std_01(&dt->err);
			return (true);
		}
		j++;
	}
	return (false);
}
