/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:30:49 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:00:11 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	set_str_arg(t_err *err, char **str, char *arg)
{
	*str = ft_strdup(arg);
	if (str == NULL)
	{
		set_err_var_01(err, true, FATAL, errno);
		err->v.str = "ARG";
		log_hist_err(err);
		return (true);
	}
	return (false);
}

t_bool	set_str_arg_builtin(t_err *err, char **str, char *arg)
{
	register size_t	i;
	register size_t	size;

	i = 0;
	size = ft_strlen(arg);
	*str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
	{
		set_err_var_01(err, true, FATAL, errno);
		err->v.str = "ARG";
		return (true);
	}
	while (i < size)
	{
		(*str)[i] = arg[i];
		i++;
	}
	(*str)[i] = '\0';
	return (false);
}
