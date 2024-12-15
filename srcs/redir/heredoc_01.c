/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:20:01 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 15:48:18 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	chk_exp_hd(t_data *dt, char **line, char *eof, t_bool *ks)
{
	if ((ft_strchk(*line, eof) == false))
	{
		if (dt->hd.isquote == false)
		{
			if (ft_exp_heredoc(dt, line) == true)
			{
				free_str(line);
				return ;
			}
		}
		ft_putstr_fd(*line, dt->hd.pipe.fd[1]);
		write(dt->hd.pipe.fd[1], "\n", 1);
	}
	else
		*ks = true;
	return ;
}

static t_bool	ft_exit_core_hd(char *line, char *eof)
{
	if (line == NULL && g_status != 130)
	{
		print_err_doc_exit(eof);
		return (true);
	}
	else if (g_status == 130)
		return (true);
	return (false);
}

static t_bool	ft_readline(t_data *dt, char *eof)
{
	char	*curr_line;
	t_bool	ks;
	int		backup_stdin;

	ks = false;
	g_status = 0;
	curr_line = NULL;
	if (chk_eof(dt, eof) == true)
		return (true);
	signal(SIGINT, &ft_heredoc_sig);
	backup_stdin = dup(0);
	dup2(backup_stdin, STDIN_FILENO);
	close_fd(dt, backup_stdin);
	while ((ks == false) && (g_status != 130))
	{	
		curr_line = readline("> ");
		if (ft_exit_core_hd(curr_line, eof) == true)
			break ;
		chk_exp_hd(dt, &curr_line, eof, &ks);
		free_str(&curr_line);
	}
	close_fd_hd_tab(dt);
	close_fd_hd(dt, dt->hd.pipe);
	exit_free(dt, g_status);
	return (dt->err.v.ks);
}

static void	ft_waitpid_hd(t_data *dt, pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	signal(SIGINT, &ft_handle_sig);
	if (WIFEXITED(status))
	{		
		dt->exec.exit_code = WEXITSTATUS(status);
		if (dt->exec.exit_code == 130 || g_status == 130)
		{	
			close_fd_hd_tab(dt);
			dt->hd.ks_sigc_her = true;
			if (dt->hd.enc_hd == false)
				close_fd(dt, dt->hd.pipe.fd[0]);
			g_status = 130;
		}
	}
	return ;
}

t_bool	heredoc(t_data *dt, int fd, char *var_name, int *fdin)
{
	t_bool	ks;
	pid_t	pid;
	int		status;

	(void)fd;
	ks = false;
	status = 0;
	signal(SIGINT, SIG_IGN);
	if (ft_here_pipe(dt) == true)
		return (true);
	pid = fork();
	if (!pid)
	{
		ks = ft_readline(dt, var_name);
		return (ks);
	}
	else
	{	
		signal(SIGINT, SIG_IGN);
		close_fd(dt, dt->hd.pipe.fd[1]);
	}
	ft_waitpid_hd(dt, pid, status);
	*fdin = dt->hd.pipe.fd[0];
	return (ks);
}
