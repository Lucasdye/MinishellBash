/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:58:37 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/17 18:49:26 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static void	cat_err_01(t_data *dt, t_err *err, char *src)
{
	char	*str_tmp;

	ft_buffer_m(err, &err->buff, src);
	if (dt->ks_exit == true)
	{
		ft_buffer_m(err, &err->buff, MSHL_DLG_ERR_EXIT);
	}
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

inline static void	cat_err_03(t_data *dt, t_err *err, char *src)
{
	ft_buffer_m(err, &err->buff, src);
	if (dt->ks_exit == true)
	{
		ft_buffer_m(err, &err->buff, MSHL_DLG_ERR_EXIT);
	}
	if (err->v.str != NULL)
	{
		ft_buffer_m(err, &err->buff, err->v.str);
		if (err->v.arg != NULL)
		{
			ft_buffer_m(err, &err->buff, " \'");
			ft_buffer_m(err, &err->buff, err->v.arg);
			ft_buffer_m(err, &err->buff, "\'");
		}
	}
	else if (err->v.arg != NULL)
		ft_buffer_m(err, &err->buff, err->v.arg);
	else
		ft_buffer_m(err, &err->buff, strerror(err->v.num));
	ft_buffer_m(err, &err->buff, "\n");
	return ;
}

void	set_error(t_data *dt, t_err *err, char *src)
{
	if (err->v.num == 0 && err->v.ks == true)
		err->v.num = EXIT_FAILURE;
	if ((err->v.n_grv < 2) && (INF_MODE == false))
		return ;
	if (DBG_MODE == 1)
	{
		cat_err_01(dt, err, src);
		cat_err_02(err);
	}
	else
		cat_err_03(dt, err, src);
	return ;
}
