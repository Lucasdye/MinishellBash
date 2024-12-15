/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:45:31 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 17:39:27 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_bool	init_arg_tab(t_data *dt, int argc, char **argv)
{
	register int	i;

	i = 0;
	dt->arg = calloc((argc + 1), sizeof(char *));
	if (dt->arg == NULL)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	while (i < argc)
	{
		if (set_str_arg(&dt->err, &dt->arg[i], argv[i]) == true)
			return (true);
		i++;
	}
	dt->arg[i] = NULL;
	dt->n_arg = argc;
	return (false);
}

static t_bool	init_data(t_data *dt, int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		set_err_var_01(&dt->err, false, WARNING, 2);
		dt->err.v.str = MSHL_NOT_YET_FUNC;
		log_hist_err(&dt->err);
	}
	if (init_arg_tab(dt, argc, argv) == true)
		return (true);
	if (set_envp(dt, envp) == true)
		return (true);
	if (get_pwd(dt) == true)
		return (true);
	if (get_path(dt) == true)
		return (true);
	if (ft_get_var(dt) == true)
		return (true);
	if (dt->ks_mini == false)
	{
		if (get_home(dt) == true)
			return (true);
	}
	if (ft_set_prompt_head(dt) == true)
		return (true);
	print_error(dt);
	return (false);
}

void	ft_core_exec(t_data *dt)
{
	dt->rt_line = ft_trim_white_space(dt->rt_line);
	dt->size = ft_strlen(dt->rt_line);
	add_history(dt->rt_line);
	if (ft_conform_str(dt) == false)
	{
		if (parse_rt_line(dt) == false)
		{
			if (ft_expand(dt) == false)
			{
				if (ft_check_rules(dt) == false)
				{
					if (ft_merge_tk_redir(dt) == false)
					{
						if ((exec_redir_hd(dt) == false)
							&& (dt->hd.ks_sigc_her == false))
							exec(dt, &dt->parse.tk);
					}
				}
				free((void *)dt->hd.fd);
			}
		}
		free_tk_tb(&dt->parse.tk.tab, dt->parse.tk.nbr);
	}
	return ;
}

static void	ft_core_loop(t_data *dt)
{
	while (dt->ks_end == false)
	{
		signal(SIGINT, handle_sig);
		if (ft_set_prompt(dt, dt->var.p_type) == false)
		{	
			dt->rt_line = readline((const char *)dt->var.prompt);
			if (!dt->rt_line)
			{
				write(1, MSHL_DLG_EXIT, 5);
				dt->ks_end = true;
			}
			else if (dt->rt_line[0] != '\0')
				ft_core_exec(dt);
			free(dt->rt_line);
		}
		else
			dt->ks_end = true;
		chk_error_sig(dt);
	}
	return ;
}

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_data	dt;

	dt.ks_tt = false;
	if (!isatty(STDIN_FILENO))
		dt.ks_tt = true;
	init_struct(&dt);
	if (dt.ks_tt == false)
	{
		ft_init_sig(false, false);
		if (init_data(&dt, argc, argv, envp) == false)
		{
			ft_core_loop(&dt);
			rl_clear_history();
		}
		free_all(&dt);
	}
	else
	{
		g_status = 1;
		set_err_std_01(&dt.err);
	}
	if (dt.ks_end == false)
		chk_error_sig(&dt);
	return (dt.last_err);
}
