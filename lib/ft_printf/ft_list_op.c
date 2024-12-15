/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:29:37 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/21 10:59:41 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_func_tab	ft_fill_func_tab(void)
{
	t_func_tab	ftab;

	ftab.func_conv[0] = &ft_fac_format_c;
	ftab.func_conv[1] = &ft_fac_format_str;
	ftab.func_conv[2] = &ft_fac_format_prt;
	ftab.func_conv[3] = &ft_fac_format_dint;
	ftab.func_conv[4] = &ft_fac_format_int;
	ftab.func_conv[5] = &ft_fac_format_uint;
	ftab.func_conv[6] = &ft_fac_format_xhex;
	ftab.func_conv[7] = &ft_fac_format_mxhex;
	ftab.func_conv[8] = &ft_fac_format_perc;
	return (ftab);
}

void	ft_init_struct(t_print *dt)
{
	dt->ks_ctrl_err = FALSE;
	dt->ks_ctrl_flow = FALSE;
	dt->ks_flg_spc = FALSE;
	dt->t_spc = '\0';
	dt->prev_flg_spc = '\0';
	dt->len_s = 0;
	dt->char_count = 0;
	dt->size_buff = BUFFER_SIZE;
	dt->idx_buff = 0;
	dt->char_tmp[0] = '\0';
	dt->char_tmp[1] = '\0';
	dt->nbr_prec = 0;
	dt->ks_padd = FALSE;
	dt->nbr_padd = 0;
	dt->char_padd = '\0';
	dt->sharp = FALSE;
	dt->minus = FALSE;
	dt->plus = FALSE;
	dt->space = FALSE;
	dt->zero = FALSE;
	dt->dot = FALSE;
	dt->outprint = STDOUT_FILENO + PERR_MODE;
	return ;
}
