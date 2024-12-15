/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:00:19 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/19 16:55:24 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_sig(t_bool flg, t_bool src)
{
	if (!flg && (src == false))
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (!flg && (src == true))
	{
		signal(SIGINT, ft_heredoc_sig);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flg)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	return ;
}

void	handle_sig(int n_sig)
{
	if (n_sig == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_redisplay();
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	return ;
}

void	ft_handle_sig(int n_sig)
{
	if (n_sig == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_redisplay();
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	return ;
}

void	ft_heredoc_sig(int n_sig)
{
	(void)n_sig;
	g_status = 130;
	close(STDIN_FILENO);
	return ;
}
/*
void	ft_heredoc_sig(int n_sig)
{
	(void)n_sig;
	g_status = 130;
	close(STDIN_FILENO);
	rl_redisplay();
	rl_replace_line("", 0);
	return ;
}
*/
