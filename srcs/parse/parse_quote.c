/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:14:18 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:41:55 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_flg_quote(t_quote *quote)
{
	quote->ks = false;
	quote->type = '\0';
	quote->dir = out;
	return ;
}

void	ft_set_flg_quote(t_quote *quote, char c)
{
	if (quote->ks == false)
	{
		quote->ks = true;
		quote->dir = in;
		quote->type = c;
	}
	else if ((quote->ks == true) && (quote->type == c))
	{
		quote->ks = false;
		quote->dir = out;
		quote->type = '\0';
	}
	return ;
}

t_bool	ft_set_tk_quote(t_data *dt, char c, size_t subtype)
{
	char	s1[2];

	s1[0] = c;
	s1[1] = '\0';
	if (dt->parse.quote.ks == false)
	{
		dt->parse.quote.ks = true;
		dt->parse.quote.dir = in;
		dt->parse.quote.type = c;
	}
	else if ((dt->parse.quote.ks == true) && (dt->parse.quote.type == c))
	{
		dt->parse.quote.ks = false;
		dt->parse.quote.dir = out;
	}
	else
		return (false);
	if (set_token(dt, s1, tk_quote, subtype) == true)
		return (true);
	dt->parse.idx.start = dt->parse.idx.end + 1;
	return (false);
}

t_bool	ft_ctrl_tk_quote(t_data *dt)
{
	if ((dt->parse.quote.ks == true) || (dt->parse.quote.dir == in))
	{
		set_err_var_01(&dt->err, true, NORMAL, 22);
		dt->err.v.str = MSHL_PARSE_UNBALANCED_QUOTE;
		log_hist_err(&dt->err);
		return (true);
	}
	return (false);
}
