/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:25:22 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 15:13:03 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_error_data(t_err *err)
{
	err->v.ks = false;
	err->v.n_grv = 0;
	err->v.num = 0;
	err->v.str = NULL;
	err->v.arg = NULL;
	err->buff.str = NULL;
	err->buff.size = 0;
	err->buff.idx = 0;
	err->h_max.n_grv = 0;
	err->hist_err = NULL;
	return ;
}

void	init_tk_tab_cmdb(t_data *dt)
{
	dt->parse.ftab[c_echo].name = "echo";
	dt->parse.ftab[c_echo].func = &ft_echo;
	dt->parse.ftab[c_cd].name = "cd";
	dt->parse.ftab[c_cd].func = &ft_cd;
	dt->parse.ftab[c_pwd].name = "pwd";
	dt->parse.ftab[c_pwd].func = &ft_pwd;
	dt->parse.ftab[c_export].name = "export";
	dt->parse.ftab[c_export].func = &ft_export_env;
	dt->parse.ftab[c_unset].name = "unset";
	dt->parse.ftab[c_unset].func = &ft_unset_env;
	dt->parse.ftab[c_env].name = "env";
	dt->parse.ftab[c_env].func = &ft_env;
	dt->parse.ftab[c_exit].name = "exit";
	dt->parse.ftab[c_exit].func = &ft_exit;
	return ;
}

void	init_tk_tab_type(t_data *dt)
{
	dt->parse.t_tk_tab[tk_none] = "_none";
	dt->parse.t_tk_tab[tk_op] = "_op";
	dt->parse.t_tk_tab[tk_ctrl_op] = "_ctrl";
	dt->parse.t_tk_tab[tk_redir_op] = "_redir";
	dt->parse.t_tk_tab[tk_fd] = "_fd";
	dt->parse.t_tk_tab[tk_file] = "_file";
	dt->parse.t_tk_tab[tk_label] = "_label";
	dt->parse.t_tk_tab[tk_cmd_b] = "_cmd_b";
	dt->parse.t_tk_tab[tk_cmd] = "_cmd";
	dt->parse.t_tk_tab[tk_var] = "_var";
	dt->parse.t_tk_tab[tk_exp] = "_exp";
	dt->parse.t_tk_tab[tk_sep] = "_sep";
	dt->parse.t_tk_tab[tk_quote] = "_quote";
	dt->parse.t_tk_tab[tk_word] = "_word";
	return ;
}

static void	init_struct_dt(t_data *dt)
{
	dt->arg = NULL;
	dt->env.tab = NULL;
	dt->ks_end = false;
	dt->ks_exit = false;
	dt->hd.ks_sigc_her = false;
	dt->var.pwd = NULL;
	dt->var.home = NULL;
	dt->var.path = NULL;
	dt->var.hostname = NULL;
	dt->var.user = NULL;
	dt->var.prompt = NULL;
	dt->var.prompt_head = NULL;
	dt->var.p_prnt = NULL;
	dt->var.p_type = p_deflt;
	dt->var.ks_err_path = false;
	dt->tmp.str = NULL;
	dt->last_err = 0;
	dt->var.fd.in = STDIN_FILENO;
	dt->var.fd.out = STDOUT_FILENO;
	dt->hd.enc_hd = false;
	init_tk_tab_cmdb(dt);
}

void	init_struct(t_data *dt)
{
	init_error_data(&dt->err);
	init_struct_dt(dt);
	init_tk_tab_type(dt);
	init_tk_tab_redir(dt);
	init_tk_tab_sep(dt);
	return ;
}
