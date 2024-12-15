/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 10:19:20 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/10 13:11:08 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static void	init_tk_tab_redir_01(t_data *dt)
{
	dt->parse.rtab[none].str = "";
	dt->parse.rtab[none].size = 0;
	dt->parse.rtab[none].flg = NONE;
	dt->parse.rtab[none].rdr = FDNONE;
	dt->parse.rtab[none].opt = false;
	dt->parse.rtab[redir_l].str = "<";
	dt->parse.rtab[redir_l].size = 1;
	dt->parse.rtab[redir_l].flg = READ;
	dt->parse.rtab[redir_l].rdr = FDIN;
	dt->parse.rtab[redir_l].opt = false;
	dt->parse.rtab[redir_r].str = ">";
	dt->parse.rtab[redir_r].size = 1;
	dt->parse.rtab[redir_r].flg = WRITE;
	dt->parse.rtab[redir_r].rdr = FDOUT;
	dt->parse.rtab[redir_r].opt = false;
	dt->parse.rtab[redir_inp].str = "<<";
	dt->parse.rtab[redir_inp].size = 2;
	dt->parse.rtab[redir_inp].flg = TRUNC;
	dt->parse.rtab[redir_inp].rdr = FDIN;
	dt->parse.rtab[redir_inp].opt = false;
	return ;
}

inline static void	init_tk_tab_redir_02(t_data *dt)
{
	dt->parse.rtab[redir_app].str = ">>";
	dt->parse.rtab[redir_app].size = 2;
	dt->parse.rtab[redir_app].flg = APPEND;
	dt->parse.rtab[redir_app].rdr = FDOUT;
	dt->parse.rtab[redir_app].opt = false;
	dt->parse.rtab[redir_pipe].str = "|";
	dt->parse.rtab[redir_pipe].size = 1;
	dt->parse.rtab[redir_pipe].flg = NONE;
	dt->parse.rtab[redir_pipe].rdr = FDNONE;
	dt->parse.rtab[redir_pipe].opt = false;
	dt->parse.rtab[redir_rp].str = ">|";
	dt->parse.rtab[redir_rp].size = 2;
	dt->parse.rtab[redir_rp].flg = WRITE;
	dt->parse.rtab[redir_rp].rdr = FDOUT;
	dt->parse.rtab[redir_rp].opt = false;
	dt->parse.rtab[redir_s_inp].str = "<<-";
	dt->parse.rtab[redir_s_inp].size = 3;
	dt->parse.rtab[redir_s_inp].flg = TRUNC;
	dt->parse.rtab[redir_s_inp].rdr = FDIN;
	dt->parse.rtab[redir_s_inp].opt = false;
	return ;
}

inline static void	init_tk_tab_redir_03(t_data *dt)
{
	dt->parse.rtab[redir_movin].str = ">&";
	dt->parse.rtab[redir_movin].size = 2;
	dt->parse.rtab[redir_movin].flg = NONE;
	dt->parse.rtab[redir_movin].rdr = FDOUT;
	dt->parse.rtab[redir_movin].opt = true;
	dt->parse.rtab[redir_movout].str = "<&";
	dt->parse.rtab[redir_movout].size = 2;
	dt->parse.rtab[redir_movout].flg = NONE;
	dt->parse.rtab[redir_movout].rdr = FDIN;
	dt->parse.rtab[redir_movout].opt = true;
	dt->parse.rtab[redir_rw].str = "<>";
	dt->parse.rtab[redir_rw].size = 2;
	dt->parse.rtab[redir_rw].flg = NONE;
	dt->parse.rtab[redir_rw].rdr = FDIN;
	dt->parse.rtab[redir_rw].opt = false;
	dt->parse.rtab[redir_s_app].str = "<<<";
	dt->parse.rtab[redir_s_app].size = 3;
	dt->parse.rtab[redir_s_app].flg = NONE;
	dt->parse.rtab[redir_s_app].rdr = FDIN;
	dt->parse.rtab[redir_s_app].opt = false;
	return ;
}

void	init_tk_tab_redir(t_data *dt)
{
	init_tk_tab_redir_01(dt);
	init_tk_tab_redir_02(dt);
	init_tk_tab_redir_03(dt);
	return ;
}

t_bool	init_std(t_data *dt)
{
	if (file_ops(dt, MSHL_DEF_FD0NAME, &dt->var.fd.in, READ) == true)
		return (true);
	if (file_ops(dt, MSHL_DEF_FD1NAME, &dt->var.fd.out, WRITE) == true)
		return (true);
	return (false);
}
