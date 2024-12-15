/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_split_qt_02.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:44:58 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/16 08:02:05 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_len_count( t_quote *qt, const char *str, size_t *len_s, size_t i)
{
	t_chk_str		chk;
	t_bool			ks;

	ks = false;
	while (str[i] != '\0' && (ks == false))
	{
		chk = ft_chk_quote(str[i]);
		if (chk.ks == true)
		{
			ft_set_flg_quote(qt, str[i]);
			if (qt->ks == false)
			{
				(*len_s)++;
				ks = true;
			}
			else if ((qt->ks == true) && (qt->type == str[i]))
					ks = true;
			else
				(*len_s)++;
		}
		else
			(*len_s)++;
		i++;
	}
	return ;
}
