/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:03:15 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:48:31 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_print	ft_parser_type(t_print dt, t_func_spec_conv *func_conv)
{
	if ((ft_spec_conv(dt.t_spc).kstate) == TRUE)
	{
		dt = (*func_conv[ft_spec_conv(dt.t_spc).idx_tab])(dt);
		dt.ks_flg_spc = FALSE;
	}
	else if (ft_spec_flag(dt.t_spc) == TRUE)
	{
		dt.ks_ctrl_flow = TRUE;
		dt.prev_flg_spc = dt.t_spc;
		if (dt.t_spc == '#')
			dt.sharp = TRUE;
		if (dt.t_spc == '-')
			dt.minus = TRUE;
		if (dt.t_spc == '+')
			dt.plus = TRUE;
		if (dt.t_spc == ' ')
			dt.space = TRUE;
		if (dt.t_spc == '0')
			dt.zero = TRUE;
		if (dt.t_spc == '.')
			dt.dot = TRUE;
	}
	return (dt);
}

static t_print	ft_parser_format(t_print dt, const char *format,
	t_func_spec_conv *func_conv)
{
	register size_t	i;

	i = 0;
	while (format[i])
	{
		if ((format[i] == '%') && (dt.ks_flg_spc == FALSE))
			dt.ks_flg_spc = TRUE;
		else if (dt.ks_flg_spc == TRUE)
		{
			dt.t_spc = format[i];
			if (dt.ks_ctrl_flow == TRUE)
				dt = ft_flag_check(dt);
			dt = ft_parser_type(dt, func_conv);
		}
		else
		{
			dt = fill_str_to_char(dt, format[i]);
		}
		if (dt.ks_ctrl_err == TRUE)
			return (dt);
		i++;
	}
	return (dt);
}

int	ft_printf(const char *format, ...)
{
	t_print				dt;
	t_func_tab			ftab;

	if (!format)
		return (EOF);
	dt.str_tmp = malloc(sizeof(char) * 2);
	if (dt.str_tmp == NULL)
		return (EOF);
	dt.str_buff = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (dt.str_buff == NULL)
		return (EOF);
	ftab = ft_fill_func_tab();
	ft_init_struct(&dt);
	if (dt.ks_ctrl_err == TRUE)
		return (EOF);
	va_start (dt.arg, format);
	dt = ft_parser_format(dt, format, ftab.func_conv);
	va_end (dt.arg);
	if (dt.ks_ctrl_err == TRUE)
		dt.char_count = EOF;
	else
		dt.char_count = write(dt.outprint, dt.str_buff, dt.idx_buff);
	free(dt.str_tmp);
	free(dt.str_buff);
	return (dt.char_count);
}

inline static char	init_printf(t_print *dt)
{
	dt->str_tmp = malloc(sizeof(char) * 2);
	if (dt->str_tmp == NULL)
	{	
		set_exit_err(dt);
		return (TRUE);
	}
	dt->str_buff = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (dt->str_buff == NULL)
	{
		set_exit_err(dt);
		return (TRUE);
	}
	return (FALSE);
}

t_exit	ft_sprintf(const char *format, ...)
{
	t_print				dt;
	t_func_tab			ftab;

	if (!format)
	{
		set_exit_err(&dt);
		return (dt.exit);
	}
	if (init_printf(&dt) == TRUE)
		return (dt.exit);
	ftab = ft_fill_func_tab();
	ft_init_struct(&dt);
	va_start (dt.arg, format);
	dt = ft_parser_format(dt, format, ftab.func_conv);
	va_end (dt.arg);
	if ((dt.ks_ctrl_err == TRUE) || (set_exit_str(&dt) == TRUE))
		set_exit_err(&dt);
	mem_free(&dt);
	return (dt.exit);
}
