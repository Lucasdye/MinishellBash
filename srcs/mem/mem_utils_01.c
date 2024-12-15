/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:19:06 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/18 09:20:50 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envp(char **tab, register size_t idx)
{
	register size_t	i;

	i = 0;
	while (i < idx)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void	free_tab_idx(void **tab, register size_t idx)
{
	register size_t	i;

	i = 0;
	while (i < idx)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void	free_tab(void **tab)
{
	register size_t	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void	free_str(char **s)
{
	if ((s) && (*s != NULL))
	{
		free(*s);
		*s = NULL;
	}
	return ;
}

void	free_all(t_data *dt)
{
	if (dt->env.tab != NULL)
		free_envp(dt->env.tab, dt->env.size);
	if (dt->arg != NULL)
		free_tab_idx((void **)dt->arg, dt->n_arg);
	if (dt->var.pwd != NULL)
		free(dt->var.pwd);
	if (dt->var.path != NULL)
		free_tab((void **)dt->var.path);
	if (dt->var.home != NULL)
		free(dt->var.home);
	if (dt->var.hostname != NULL)
		free(dt->var.hostname);
	if (dt->var.user != NULL)
		free(dt->var.user);
	if (dt->var.prompt_head != NULL)
		free(dt->var.prompt_head);
	if (dt->var.prompt != NULL)
		free(dt->var.prompt);
	if (dt->var.p_prnt != NULL)
		free(dt->var.p_prnt);
	return ;
}
