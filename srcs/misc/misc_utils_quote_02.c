/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_quote_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:18:15 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:35:31 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_trim_quote(char *s1, char c)
{
	char	*str;
	char	set[2];

	if (!s1)
		return (NULL);
	if (!c)
		return (s1);
	set[0] = c;
	set[1] = '\0';
	str = ft_strtrim(s1, set);
	free(s1);
	return (str);
}

static void	chk_err_qt(t_data *dt, t_chk_str_e	*chk, char **str)
{
	*str = ft_trim_white_space(*str);
	chk->s = ft_chk_quote((*str)[0]);
	if ((chk->s.ks == true) && (*str)[0] != (*str)[ft_strlen(*str) - 1])
	{
		chk->ks = true;
		set_err_var_01(&dt->err, true, NORMAL, 1);
		dt->err.v.str = MSHL_PARSE_UNBALANCED_QUOTE;
		log_hist_err(&dt->err);
	}	
	return ;
}

t_chk_str_e	ft_clean_str_quote_ext(t_data *dt, char **str)
{
	t_chk_str_e	chk;

	chk.ks = false;
	chk.s.ks = false;
	chk.s.idx = 0;
	if (str)
	{
		chk_err_qt(dt, &chk, str);
		if (chk.ks == true)
			return (chk);
		if (chk.s.ks == false || ((chk.s.ks == true)
				&& (QUOTE[chk.s.idx] == DQUOTE)))
			chk.s.idx = true;
		else
			chk.s.idx = false;
		if (chk.s.ks == true)
		{
			*str = ft_trim_quote(*str, (*str)[0]);
			if (*str != NULL)
				return (chk);
			set_err_std_01(&dt->err);
			chk.ks = true;
		}
	}
	return (chk);
}

static void	ft_chk_move_qt(t_quote *qt, char **str, size_t *i, size_t len_s)
{
	t_chk_str	chk;

	chk = ft_chk_quote((*str)[*i]);
	if (chk.ks == true)
	{
		if ((qt->ks == false) || ((qt->ks == true) && (qt->type == (*str)[*i])))
		{	
			ft_memmove(&(*str)[*i], &(*str)[*i + 1], (len_s - *i));
			len_s--;
		}
		else
			(*i)++;
		ft_set_flg_quote(qt, QUOTE[chk.idx]);
	}
	else
		(*i)++;
	return ;
}

t_bool	ft_clean_str_quote(t_data *dt, t_quote *qt, char **str)
{
	size_t		i;
	size_t		len_s;

	i = 0;
	if (!str)
	{
		set_err_var_01(&dt->err, true, NORMAL, 1);
		dt->err.v.str = MSHL_EINVAL;
		log_hist_err(&dt->err);
		return (true);
	}
	len_s = ft_strlen(*str);
	while ((*str)[i] != '\0')
		ft_chk_move_qt(qt, str, &i, len_s);
	return (false);
}
