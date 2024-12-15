/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_split_qt_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:48:09 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 10:09:42 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static void	ft_c_count( t_quote *qt, const char *str, size_t *nb_substr
	, size_t i)
{
	t_chk_str	chk;

	while (str[i] != '\0')
	{
		chk = ft_chk_quote(str[i]);
		if (chk.ks == true)
		{
			ft_set_flg_quote(qt, str[i]);
			if (((qt->ks == false) && (str[i + 1] != '\0'))
				|| (((qt->ks == true) && (qt->type == str[i]))
					&& (ft_chk_quote(str[i - 1]).ks == false)))
				*nb_substr += 1;
		}
		i++;
	}
	return ;
}

size_t	ft_substr_count(char const *str)
{
	size_t		nb_substr;
	size_t		i;
	t_chk_str	chk;
	t_quote		qt;

	nb_substr = 0;
	i = 0;
	ft_init_flg_quote(&qt);
	if (str[i] != '\0')
		nb_substr = 1;
	chk = ft_chk_quote(str[i]);
	if (chk.ks == true)
	{
		ft_set_flg_quote(&qt, str[i]);
		i++;
	}
	ft_c_count(&qt, str, &nb_substr, i);
	return (nb_substr);
}

static size_t	ft_len_str(char const *str)
{
	register size_t	i;
	size_t			len_s;
	t_chk_str		chk;
	t_quote			qt;

	ft_init_flg_quote(&qt);
	len_s = 0;
	i = 0;
	chk = ft_chk_quote(str[i]);
	if (chk.ks == true)
	{
		ft_set_flg_quote(&qt, str[i]);
		len_s++;
		i++;
	}
	ft_len_count(&qt, str, &len_s, i);
	return (len_s);
}

static	char	**ft_char_trim(char **tab_s, char const *str
	, register size_t nb_str)
{
	register size_t	i;
	register size_t	len_str;

	i = 0;
	while (i < nb_str)
	{
		len_str = ft_len_str(str);
		tab_s[i] = (char *)malloc(sizeof (**tab_s) *(len_str + 1));
		if (tab_s[i] == NULL)
		{
			free_tab_idx((void *)&tab_s, i);
			return (NULL);
		}
		ft_strlcpy(tab_s[i], str, len_str);
		str += len_str;
		i++;
	}
	tab_s[i] = NULL;
	return (tab_s);
}

char	**ft_split_str_qt(char const *s)
{
	register size_t	nb_str;
	char			**tab_s;

	if (!s)
		return (NULL);
	nb_str = ft_substr_count(s);
	tab_s = (char **)malloc(sizeof (*tab_s) * (nb_str + 1));
	if (tab_s == NULL)
		return (NULL);
	tab_s = ft_char_trim(tab_s, s, nb_str);
	return (tab_s);
}
