/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_buff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:12:13 by jveuille          #+#    #+#             */
/*   Updated: 2023/09/30 10:06:32 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_init_buff_m(t_buff *buff)
{
	if (buff->str == NULL)
	{
		buff->str = ft_calloc(BUFFER_SIZE, sizeof(char));
		if (buff->str == NULL)
			return (true);
		buff->size = BUFFER_SIZE ;
	}
	return (false);
}

static t_bool	ft_dim_buffer(t_err *err, t_buff *buff, size_t size_data)
{
	char	*str_tmp;
	t_bool	redim;

	redim = false;
	while ((buff->size - buff->idx) <= size_data)
	{
		buff->size *= 2;
		redim = true;
	}
	if (redim == TRUE)
	{
		if (set_str_arg(err, &str_tmp, buff->str) == true)
			return (true);
		free(buff->str);
		buff->str = ft_calloc(buff->size, sizeof(char));
		if (buff->str == NULL)
		{
			free(str_tmp);
			return (true);
		}
		ft_strcat_m(buff->str, str_tmp);
		free(str_tmp);
	}
	return (false);
}

t_bool	ft_buffer_m(t_err *err, t_buff *buff, char *add_str)
{
	register size_t	i;
	register size_t	len_s;

	len_s = ft_strlen(add_str);
	if (ft_dim_buffer(err, buff, len_s) == true)
		return (true);
	i = 0;
	while (i < len_s)
	{
		buff->str[(buff->idx) + i] = add_str[i];
		i++;
	}
	buff->idx += i;
	return (false);
}
