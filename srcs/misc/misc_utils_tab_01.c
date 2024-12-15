/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_tab_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:35:26 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:34:18 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* recherche chaine dans un tableau , renvoi  booleen et index de position*/
t_chk_stab	ft_isstr_tab(char *s1, char **tab)
{
	t_chk_stab		t_chk;
	register size_t	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (ft_strchk(s1, tab[i]) == true)
		{
			t_chk.ks = true;
			t_chk.idx = i;
			return (t_chk);
		}
		i++;
	}
	t_chk.ks = false;
	return (t_chk);
}

t_chk_stab	ft_isstr_tab_sz(char *s1, char **tab, register size_t size)
{
	t_chk_stab		chk;
	register size_t	i;
	t_bool			ks;

	ks = false;
	i = 0 ;
	while ((i < size) && (ks == false))
	{
		if (ft_strchk(s1, tab[i]) == true)
			ks = true;
		else
			i++;
	}
	chk.ks = ks;
	chk.idx = i;
	return (chk);
}

t_chk_stab	ft_isstr_tab_redir(char *s1, t_redir *tab, register size_t size)
{
	t_chk_stab		chk;
	register size_t	i;
	t_bool			ks;

	ks = false;
	i = 0 ;
	while ((i < size) && (ks == false))
	{
		if (ft_strchk(s1, tab[i].str) == true)
			ks = true;
		else
			i++;
	}
	chk.ks = ks;
	chk.idx = i;
	return (chk);
}
