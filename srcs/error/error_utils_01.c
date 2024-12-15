/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 10:56:21 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/18 09:17:06 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static void	cat_err_01(t_data *dt, t_err_var content)
{
	char	*str_tmp;

	ft_buffer_m(&dt->err, &dt->err.buff, MSHL_DLG_ERROR);
	if (dt->ks_exit == true)
	{
		ft_buffer_m(&dt->err, &dt->err.buff, MSHL_DLG_ERR_EXIT);
	}
	if (content.n_grv > 1)
	{
		ft_buffer_m(&dt->err, &dt->err.buff, " [Error ");
		ft_buffer_m(&dt->err, &dt->err.buff,
			set_err_tab(&dt->err, content.n_grv));
	}
	else
	{	
		ft_buffer_m(&dt->err, &dt->err.buff, " [");
		ft_buffer_m(&dt->err, &dt->err.buff,
			set_err_tab(&dt->err, content.n_grv));
	}
	ft_buffer_m(&dt->err, &dt->err.buff, "], error code [");
	str_tmp = ft_itoa(content.num);
	ft_buffer_m(&dt->err, &dt->err.buff, str_tmp);
	free(str_tmp);
	ft_buffer_m(&dt->err, &dt->err.buff, "]:");
}

inline static void	cat_err_02(t_data *dt, t_err_var content)
{
	ft_buffer_m(&dt->err, &dt->err.buff, content.str);
	if (content.arg != NULL)
	{
		ft_buffer_m(&dt->err, &dt->err.buff, " \"");
		ft_buffer_m(&dt->err, &dt->err.buff, content.arg);
		ft_buffer_m(&dt->err, &dt->err.buff, "\", ");
	}
	ft_buffer_m(&dt->err, &dt->err.buff, ", ");
	ft_buffer_m(&dt->err, &dt->err.buff, strerror(content.num));
	ft_buffer_m(&dt->err, &dt->err.buff, "\n");
}

inline static void	cat_err_03(t_data *dt, t_err_var content)
{
	ft_buffer_m(&dt->err, &dt->err.buff, MSHL_DLG_ERROR);
	if (dt->ks_exit == true)
	{
		ft_buffer_m(&dt->err, &dt->err.buff, MSHL_DLG_ERR_EXIT);
	}
	if (content.str != NULL)
	{
		ft_buffer_m(&dt->err, &dt->err.buff, content.str);
		if (content.arg != NULL)
		{
			ft_buffer_m(&dt->err, &dt->err.buff, " \'");
			ft_buffer_m(&dt->err, &dt->err.buff, content.arg);
			ft_buffer_m(&dt->err, &dt->err.buff, "\'");
		}
	}
	else if (content.arg != NULL)
		ft_buffer_m(&dt->err, &dt->err.buff, content.arg);
	else
		ft_buffer_m(&dt->err, &dt->err.buff, strerror(content.num));
	ft_buffer_m(&dt->err, &dt->err.buff, "\n");
	return ;
}

void	extract_err(t_data *dt, t_err_var content)
{
	if (ERR_MODE == true)
	{
		if ((content.n_grv > dt->err.h_max.n_grv)
			|| ((content.n_grv == dt->err.h_max.n_grv)
				&& (content.lvl > dt->err.h_max.lvl)))
		{
			dt->err.h_max.n_grv = content.n_grv;
			dt->err.h_max.lvl = dt->err.h_max.lvl;
			dt->err.v.num = content.num;
		}
	}
	if ((content.num == 0) && (content.ks == true))
		content.num = EXIT_FAILURE;
	if ((content.n_grv < 2) && (INF_MODE == false))
		return ;
	if (DBG_MODE == 1)
	{
		cat_err_01(dt, content);
		cat_err_02(dt, content);
	}
	else
		cat_err_03(dt, content);
	return ;
}

void	print_error(t_data *dt)
{
	if (dt->err.v.ks == true || (dt->err.v.num != 0 && INF_MODE == true))
	{
		init_error_tab(&dt->err);
		if (ft_init_buff_m(&dt->err.buff) == true)
			return ;
		if (dt->err.hist_err != NULL)
			lstiter_err_01(dt, dt->err.hist_err, &extract_err);
		else
			set_error(dt, &dt->err, MSHL_DLG_ERROR);
		write(STDERR_FILENO, dt->err.buff.str, ft_strlen(dt->err.buff.str));
		free(dt->err.buff.str);
		dt->err.buff.str = NULL;
		dt->err.buff.size = 0;
		dt->err.buff.idx = 0;
	}
	clear_hist_err(&dt->err);
	if (dt->err.v.arg != NULL)
		free(dt->err.v.arg);
	init_error_data(&dt->err);
	return ;
}
