/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:56:36 by lbouguet          #+#    #+#             */
/*   Updated: 2023/11/21 15:04:02 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static int	set_err_over(t_data *dt)
{
	set_err_var_01(&dt->err, true, NORMAL, 1);
	dt->err.v.str = MSHL_OVER_ARG;
	log_hist_err(&dt->err);
	return (1);
}

inline static int	set_err_bnum(t_data *dt)
{
	set_err_var_01(&dt->err, true, NORMAL, 2);
	dt->err.v.str = MSHL_BAD_NUM_ARG;
	log_hist_err(&dt->err);
	return (2);
}

inline static t_bool	chk_err_over(t_data *dt, char *varname, int num)
{
	t_bool	ks;
	char	*snum;
	char	*s1;

	ks = false;
	if (set_str_arg(&dt->err, &s1, varname) == true)
		return (true);
	snum = ft_itoa(num);
	if (s1[0] == PLUS)
		ft_memmove(s1, s1 + 1, ft_strlen(snum) + 1);
	if (ft_strchk(s1, snum) == false)
		ks = true;
	free(s1);
	free(snum);
	return (ks);
}

inline static void	set_n_exit(t_data *dt, char **var_name, int *n_exit)
{
	if (ft_tablen(var_name) > 1)
			*n_exit = set_err_over(dt);
	else
	{
		if (ft_isnum_str(var_name[0]) == false)
			*n_exit = set_err_bnum(dt);
		else
		{
			*n_exit = ft_atol(var_name[0]);
			if (*n_exit < 0)
				*n_exit = *n_exit % 256;
			else
			{
				if (chk_err_over(dt, var_name[0], *n_exit) == true)
					*n_exit = set_err_bnum(dt);
			}
		}
	}
	return ;
}

int	ft_exit(t_data *dt, char **var_name)
{
	int		n_exit;
	t_bool	ks;

	n_exit = 0;
	ks = false;
	if ((var_name == NULL) || (var_name[0] == NULL))
		ks = true;
	else if (var_name[0][0] == '\0')
		ks = true;
	if (ks == false)
		set_n_exit(dt, var_name, &n_exit);
	else
	{
		if (g_status > 0)
			n_exit = g_status;
		else
			n_exit = dt->last_err;
	}
	dt->ks_end = true;
	dt->ks_exit = true;
	g_status = n_exit;
	return (n_exit);
}
