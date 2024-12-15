/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:33:57 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/16 13:02:29 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tk_u(t_token **tab, register size_t idx)
{	
	register size_t	j;

	free_str(&(*tab)[idx].name);
	free_str(&(*tab)[idx].prvar);
	if ((*tab)[idx].arg != NULL)
	{
		j = 0;
		while ((*tab)[idx].arg[j] != NULL)
		{
			free((*tab)[idx].arg[j]);
			j++;
		}
		free((*tab)[idx].arg);
	}
	return ;
}

void	free_tk_tb(t_token **tab, register size_t size)
{
	register size_t	i;
	register size_t	j;

	i = 0;
	if (tab == NULL)
		return ;
	while (i < size)
	{
		free_str(&(*tab)[i].name);
		free_str(&(*tab)[i].prvar);
		if ((*tab)[i].arg != NULL)
		{
			j = 0;
			while ((*tab)[i].arg[j] != NULL)
			{
				free((*tab)[i].arg[j]);
				j++;
			}
			free((*tab)[i].arg);
		}
		i++;
	}
	free(*tab);
	*tab = NULL;
	return ;
}
