/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_excd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 08:28:13 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:30:15 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_expand_exitcode(t_data *dt, char **s1)
{
	char				*str;
	register t_bool		ks;

	ks = false;
	str = ft_lltoa(g_status);
	if (str == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	free(*s1);
	*s1 = NULL;
	if (set_str_arg(&dt->err, s1, str) == true)
		ks = true;
	free(str);
	return (ks);
}
