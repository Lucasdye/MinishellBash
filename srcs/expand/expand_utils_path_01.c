/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_path_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:50:45 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/25 11:31:24 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_get_exp_opt(t_data *dt, char *src
	, register size_t idx, char ***ptr_var)
{
	if (src[1] == PLUS)
	{
		idx++;
		*ptr_var = &dt->var.pwd;
	}
	else
		*ptr_var = &dt->var.home;
	if (get_home(dt) == true)
		return (true);
	return (false);
}

t_bool	ft_expand_path(t_data *dt, char **dest, char *src, register size_t idx)
{
	register size_t	i;
	register size_t	len_s;
	char			**ptr_var;

	if (ft_get_exp_opt(dt, src, idx, &ptr_var) == true)
		return (true);
	len_s = ft_strlen(*ptr_var);
	if (dt->var.home == NULL)
		return (true);
	*dest = ft_calloc((len_s + ft_strlen(src) + 2 - idx), sizeof(char));
	if (dest == NULL)
	{	
		set_err_std_01(&dt->err);
		return (true);
	}
	*dest = ft_strcat_m(*dest, *ptr_var);
	(*dest)[len_s] = '/';
	i = 0;
	while (src[i + idx] != '\0')
	{
		(*dest)[len_s + i + 1] = src[i + idx];
		i++;
	}
	(*dest)[len_s + i + 1] = '\0';
	return (false);
}

t_bool	ft_expand_path_01(t_data *dt, char **dest, register size_t idx)
{
	char	*s_tmp;

	if (set_str_arg(&dt->err, &s_tmp, *dest) == true)
		return (true);
	free(*dest);
	if (ft_expand_path(dt, dest, s_tmp, idx) == true)
	{
		free(s_tmp);
		return (true);
	}
	free(s_tmp);
	return (false);
}
