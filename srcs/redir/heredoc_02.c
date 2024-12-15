/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:06:46 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 14:01:17 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_set_heredoc(t_data *dt, register size_t idx)
{
	if (heredoc(dt, ft_atoi(dt->parse.tk.tab[idx].arg[0]),
			dt->parse.tk.tab[idx].arg[1], &dt->hd.fd[dt->hd.idx]))
		return (true);
	dt->hd.enc_hd = true;
	return (false);
}

t_bool	ft_exp_heredoc(t_data *dt, char **s1)
{
	if (ft_exp_core_var(dt, s1) == true)
		return (true);
	return (false);
}
