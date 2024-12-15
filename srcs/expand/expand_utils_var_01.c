/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_var_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:22:20 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:30:44 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dup	ft_var_dup(const char *s, register size_t s_idx_init
	, register size_t s_idx_max)
{
	t_dup	dst;

	dst.str = NULL;
	if (!(s && s_idx_max) || (s_idx_init > s_idx_max))
		return (dst);
	dst.ptr = s_idx_init;
	while ((s[dst.ptr] != '\0') && (dst.ptr < s_idx_max)
		&& (ft_isalnum_var(s[dst.ptr]) == true))
		dst.ptr++;
	dst.str = malloc(sizeof(char) * ((dst.ptr - s_idx_init) + 1));
	if (dst.str != NULL)
	{
		dst.size = 0;
		while (dst.size < (dst.ptr - s_idx_init))
		{
			dst.str[dst.size] = s[s_idx_init + dst.size];
			dst.size++;
		}
		dst.str[dst.size] = '\0';
	}
	return (dst);
}

t_bool	ft_var_read_line( t_exp_var *sd, t_dup *dst, t_dup *src)
{
	sd->ks_ls = false;
	if ((sd->ks_ls == false) && (sd->ks_end_s == false))
	{
		*dst = ft_strdup_obj(src->str, '$', src->ptr, src->size);
		if (dst->str == NULL)
			return (true);
		src->ptr = dst->ptr;
		if (src->str[src->ptr] == '$')
		{
			sd->ks_ls = true;
		}
		if (dst->ptr == src->size)
			sd->ks_end_s = true;
	}
	return (false);
}

t_bool	ft_expand_var(t_data *dt, char *str, register size_t idx)
{
	char	*s1;

	free(dt->parse.tk.tab[idx].name);
	s1 = get_env_var(dt, str);
	if ((s1 == NULL) || (str == NULL))
	{
		dt->parse.tk.tab[idx].name = NULL;
		set_err_std_01(&dt->err);
		return (true);
	}
	else
	{
		if (set_str_arg(&dt->err, &dt->parse.tk.tab[idx].name, s1) == true)
		{
			free (s1);
			set_err_std_01(&dt->err);
			return (true);
		}
		free(s1);
	}
	return (false);
}
