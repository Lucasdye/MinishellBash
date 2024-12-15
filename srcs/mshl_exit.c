/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:26:04 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 13:19:20 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_free(t_data *dt, int status)
{
	free((void *)dt->hd.fd);
	free_tk_tb(&dt->parse.tk.tab, dt->parse.tk.nbr);
	clear_hist_err(&dt->err);
	free_all(dt);
	free(dt->rt_line);
	rl_clear_history();
	chk_error_sig(dt);
	exit(status);
}
