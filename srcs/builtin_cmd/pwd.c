/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:56:42 by lbouguet          #+#    #+#             */
/*   Updated: 2023/11/21 09:02:46 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_err_pwd(t_err *err)
{
	set_err_var_01(err, true, NORMAL, 1);
	err->v.str = MSHL_NOT_YET_ARG;
	return ;
}

static t_bool	ft_print_pwd(t_err *err, char *dir)
{
	t_bool	ks;

	ks = ft_swrite(err, dir, STDOUT_FILENO);
	if (ks == false)
			ks = ft_swrite(err, "\n", STDOUT_FILENO);
	return (ks);
}

int	ft_pwd(t_data *dt, char **var_name)
{
	char	*current_dir;
	t_err	err;

	(void)dt;
	init_error_data(&err);
	if ((var_name != NULL) && (var_name[0] != NULL))
		set_err_pwd(&err);
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		if (dt->var.pwd != NULL)
			ft_print_pwd(&err, dt->var.pwd);
		else
		{
			set_err_var_01(&err, true, NORMAL, errno);
			err.v.str = strerror(errno);
		}
	}
	else
		ft_print_pwd(&err, current_dir);
	free(current_dir);
	if (err.v.ks == true)
		print_builtin_error(&err, MSHL_DLG_ERR_PWD);
	return (err.v.num);
}
