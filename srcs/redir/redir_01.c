/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:56:58 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:45:55 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_err_redir_01(t_data *dt)
{
	set_err_var_01(&dt->err, true, NORMAL, 2);
	dt->err.v.str = MSHL_PARSE_BAD_TOKEN;
	log_hist_err(&dt->err);
	return ;
}

static void	set_err_redir_02(t_data *dt, char **src)
{
	set_err_var_01(&dt->err, true, NORMAL, errno);
	set_str_arg(&dt->err, &dt->err.v.str, *src);
	log_hist_err(&dt->err);
	return ;
}

static t_bool	ft_chk_dir(t_data *dt, size_t idx)
{
	t_kstr	chk;
	t_bool	ks;

	ks = false;
	chk = ft_get_path(dt, dt->parse.tk.tab[idx].arg[1]);
	if (chk.ks == true)
		return (true);
	if (chk.str[0] == '\0')
	{
		free(chk.str);
		if (set_str_arg(&dt->err, &chk.str, CUR_DIR) == true)
			return (true);
	}
	if (access(chk.str, (F_OK | W_OK)) != 0)
	{
		set_err_redir_02(dt, &dt->parse.tk.tab[idx].arg[1]);
		ks = true;
	}
	free(chk.str);
	return (ks);
}

t_bool	ft_redir_input(t_data *dt, size_t idx, t_flag flag)
{
	int		fd;

	if (&dt->parse.tk.tab[idx] != NULL)
	{
		if (access(dt->parse.tk.tab[idx].name
				, (F_OK | R_OK)) == 0)
		{
			if (file_ops(dt, dt->parse.tk.tab[idx].arg[1]
					, &fd, flag) == false)
			{
				if (dup2_src_fd(dt, &fd, STDIN_FILENO) == true)
					return (true);
				return (false);
			}
		}
		set_err_redir_02(dt, &dt->parse.tk.tab[idx].arg[1]);
		return (true);
	}
	set_err_redir_01(dt);
	return (true);
}

t_bool	ft_redir_output(t_data *dt, size_t idx, t_flag flag)
{
	int		fd;

	if (&dt->parse.tk.tab[idx] != NULL)
	{
		if (ft_chk_dir(dt, idx) == false)
		{
			if (file_ops(dt, dt->parse.tk.tab[idx].arg[1]
					, &fd, flag) == false)
			{
				if (dup2_src_fd(dt, &fd, STDOUT_FILENO) == true)
					return (true);
				return (false);
			}
		}
		return (true);
	}
	set_err_redir_01(dt);
	return (true);
}
