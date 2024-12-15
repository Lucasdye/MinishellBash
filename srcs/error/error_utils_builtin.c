/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:02:20 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/18 18:59:00 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static void	cat_err_01(t_err *err, char *src)
{
	char	*str_tmp;

	ft_buffer_m(err, &err->buff, src);
	if (err->v.n_grv > 1)
	{
		ft_buffer_m(err, &err->buff, " [Error ");
		ft_buffer_m(err, &err->buff, set_err_tab(err, err->v.n_grv));
	}
	else
	{	
		ft_buffer_m(err, &err->buff, " [");
		ft_buffer_m(err, &err->buff, set_err_tab(err, err->v.n_grv));
	}
	ft_buffer_m(err, &err->buff, "], error code [");
	str_tmp = ft_itoa(err->v.num);
	ft_buffer_m(err, &err->buff, str_tmp);
	free(str_tmp);
	ft_buffer_m(err, &err->buff, "]:");
	return ;
}

inline static void	cat_err_02(t_err *err)
{
	ft_buffer_m(err, &err->buff, err->v.str);
	if (err->v.arg != NULL)
	{
		ft_buffer_m(err, &err->buff, " \"");
		ft_buffer_m(err, &err->buff, err->v.arg);
		ft_buffer_m(err, &err->buff, "\", ");
	}
	ft_buffer_m(err, &err->buff, ", ");
	ft_buffer_m(err, &err->buff, strerror(err->v.num));
	ft_buffer_m(err, &err->buff, "\n");
	return ;
}

inline static void	cat_err_03(t_err *err, char *src)
{
	ft_buffer_m(err, &err->buff, MSHL_DLG_ERROR);
	ft_buffer_m(err, &err->buff, src);
	if (err->v.arg != NULL)
	{
		ft_buffer_m(err, &err->buff, err->v.arg);
		ft_buffer_m(err, &err->buff, ": ");
	}
	if (err->v.str != NULL)
		ft_buffer_m(err, &err->buff, err->v.str);
	else
		ft_buffer_m(err, &err->buff, strerror(err->v.num));
	ft_buffer_m(err, &err->buff, "\n");
	return ;
}

static void	set_error_builtin(t_err *err, char *src)
{
	if (err->v.num == 0 && err->v.ks == true)
		err->v.num = EXIT_FAILURE;
	if ((err->v.n_grv < 2) && (INF_MODE == false))
		return ;
	if (DBG_MODE == 1)
	{
		cat_err_01(err, src);
		cat_err_02(err);
	}
	else
		cat_err_03(err, src);
	return ;
}

void	print_builtin_error(t_err *err, char *src)
{
	init_error_tab(err);
	if (ft_init_buff_m(&err->buff) == true)
		return ;
	set_error_builtin(err, src);
	write(STDERR_FILENO, err->buff.str, err->buff.idx);
	free(err->buff.str);
	g_status = err->v.num;
	err->buff.str = NULL;
	err->buff.size = 0;
	err->buff.idx = 0;
	if (err->v.arg != NULL)
		free(err->v.arg);
	clear_hist_err(err);
	return ;
}
