/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_str_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:00:23 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/20 15:56:04 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_chk_move(char **src, t_quote qt, size_t *i,
	size_t *size)
{
	if (*i < *size)
	{
		if (qt.ks == false)
		{
			(*src)[*i] = '\x20';
			(*i)++;
			while ((*i < *size) && (ft_iswhite_space((*src)[*i]) == true))
			{
				ft_memmove(&(*src)[*i], &(*src)[*i + 1], (*size - *i));
				(*size)--;
			}
		}
		else
			(*i)++;
	}
	return ;
}

char	*ft_clean_white_space_qt(char *src)
{
	size_t	i;
	size_t	size;
	t_quote	qt;

	i = 0;
	ft_init_flg_quote(&qt);
	if (src == NULL)
		return (src);
	src = ft_trim_white_space(src);
	size = ft_strlen(src);
	while (i < (size))
	{
		while ((i < size) && (ft_iswhite_space(src[i]) == false))
		{
			if (ft_isquote(src[i], ALL) == true)
				ft_set_flg_quote(&qt, src[i]);
			i++;
		}
		ft_chk_move(&src, qt, &i, &size);
	}
	return (src);
}

t_bool	ft_swrite(t_err *err, char *s, int fd)
{
	t_bool	ks;
	ssize_t	ret;
	size_t	size;

	size = 0;
	ks = false;
	if (s)
	{
		size = ft_strlen(s);
		if (size != 0)
		{
			ret = write(fd, s, size);
			if (ret == ERR)
			{
				set_err_std_01(err);
				free_str(&err->v.arg);
				set_str_arg(err, &err->v.arg, " write error");
				log_hist_err(err);
				ks = true;
			}
		}
	}
	return (ks);
}
