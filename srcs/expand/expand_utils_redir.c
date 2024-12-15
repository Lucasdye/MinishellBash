/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:38:23 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/16 12:15:35 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_expand_arg_redir(t_data *dt, t_token *tk)
{
	register size_t	i;
	register size_t	size;

	size = ft_strlen(tk->arg[1]);
	if ((size == 1) && (tk->arg[1][0] == '-'))
		return (false);
	if ((size == 2) && (tk->arg[1][0] == '-'))
		return (false);
	i = 0;
	while ((i < size) && (ft_isdigit(tk->arg[1][i]) == true))
		i++;
	if (i == size)
		return (false);
	if (ft_var_read(dt, &tk->arg[1]) == true)
		return (true);
	return (false);
}
