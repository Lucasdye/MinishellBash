/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_split_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:08:25 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 10:09:18 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static void	ft_c_count(t_quote *qt, const char *str, size_t *nb_substr
	, size_t *i)
{
	if (qt->ks == false)
	{
		while ((ft_iswhite_space(str[*i]) == true)
			&& (ft_iswhite_space(str[*i + 1]) == true))
			(*i)++;
		if ((ft_iswhite_space(str[*i]) == true)
			&& (ft_iswhite_space(str[*i + 1]) == false)
			&& (str[*i + 1] != '\0'))
		{
			*nb_substr += 1;
		}
	}
	return ;
}

static size_t	ft_substr_count(char const *str)
{
	size_t		nb_substr;
	size_t		i;
	t_quote		qt;
	t_chk_str	chk;

	nb_substr = 0;
	i = 0;
	ft_init_flg_quote(&qt);
	if ((ft_iswhite_space(str[i]) == false) && str[i] != '\0')
		nb_substr += 1;
	while (str[i] != '\0')
	{
		chk = ft_chk_quote(str[i]);
		if (chk.ks == true)
			ft_set_flg_quote(&qt, str[i]);
		else
			ft_c_count(&qt, str, &nb_substr, &i);
		i++;
	}
	return (nb_substr);
}

static size_t	ft_len_str(char const *str, t_quote *qt)
{
	register size_t	len_str;
	register size_t	i;
	t_chk_str		chk;

	len_str = 0;
	i = 0;
	while ((str[i] != '\0')
		&& !((qt->ks == false) && (ft_iswhite_space(str[i]) == true)))
	{
		chk = ft_chk_quote(str[i]);
		if (chk.ks == true)
			ft_set_flg_quote(qt, str[i]);
		len_str++;
		i++;
	}
	return (len_str);
}

static	char	**ft_char_trim(char **tab_s, char const *str
	, register size_t nb_str)
{
	register size_t	i;
	register size_t	len_str;
	t_quote			qt;

	ft_init_flg_quote(&qt);
	i = 0;
	while (i < nb_str)
	{
		while ((*str != '\0') && (ft_iswhite_space(*str) == true))
			str++;
		len_str = ft_len_str(str, &qt);
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

char	**ft_split_str_wp(char const *s)
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
