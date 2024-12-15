/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:58:03 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:16:41 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction qui extrait le chemin actuel du tableau des variable d'environnement
t_bool	get_pwd(t_data *dt)
{
	register size_t	i;
	char			**tab_s;
	t_bool			ks;

	i = 0;
	ks = false;
	while ((dt->env.tab[i] != NULL) && (ks == false))
	{
		tab_s = ft_split(dt->env.tab[i], '=');
		if (tab_s == NULL)
		{
			set_err_std_01(&dt->err);
			return (true);
		}
		if (ft_strchk(tab_s[0], "PWD") == true)
		{
			if (dt->var.pwd != NULL)
				free (dt->var.pwd);
			if (set_str_arg(&dt->err, &dt->var.pwd, tab_s[1]) == true)
				ks = true;
		}			
		free_tab((void **)tab_s);
		i++;
	}
	return (ks);
}

t_bool	get_home(t_data *dt)
{
	register size_t	i;
	char			**tab_s;
	t_bool			ks;

	i = 0;
	ks = false;
	while ((dt->env.tab[i] != NULL) && (ks == false))
	{
		tab_s = ft_split(dt->env.tab[i], '=');
		if (tab_s == NULL)
		{
			set_err_std_01(&dt->err);
			return (true);
		}
		if (ft_strchk(tab_s[0], "HOME") == true)
		{
			if (dt->var.home != NULL)
				free_str(&dt->var.home);
			if (set_str_arg(&dt->err, &dt->var.home, tab_s[1]) == true)
				ks = true;
		}
		free_tab((void **)tab_s);
		i++;
	}
	return (ks);
}
