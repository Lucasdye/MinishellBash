/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:25:35 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 09:51:27 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_first_elem(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (str[i] < 0)
	{	
		while (str[j] < 0)
			j++;
		while (str[j])
		{
			str[i] = str[j];
			i++;
			j++;
		}
		str[i] = 0;
	}
	return ;
}

int	count_blocs_in_command_line(t_tk_tab *tk)
{
	int	i;
	int	counter;

	counter = 1;
	i = 0;
	while (i < (int)tk->idx)
	{
		if (tk->tab[i].type == tk_redir_op && tk->tab[i].subtype == redir_pipe)
			counter++;
		i++;
	}
	return (counter);
}
