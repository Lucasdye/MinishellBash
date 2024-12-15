/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:03:07 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/18 18:03:26 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_evar_join(t_env_var var)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(var.name, "=");
	if (s1 == NULL)
		return (NULL);
	s2 = ft_strjoin(s1, var.val);
	free(s1);
	return (s2);
}

/* extraction de chaine a partir d'un pointeur de debut et fin de chaine */
t_bool	set_substr_arg(char **dest, char *src, register size_t start
		, register size_t end)
{
	register size_t	i;
	register size_t	size;

	i = 0;
	if (!src || (end < start))
		return (true);
	size = ft_strlen(src);
	if (end > (size))
		end = (size);
	*dest = ft_calloc((end - start + 1), sizeof(char));
	if (*dest == NULL)
		return (true);
	while (i < end - start)
	{
		(*dest)[i] = src[i + start];
		i++;
	}
	return (false);
}

t_bool	get_substr(t_err *err, char **dest, char *src, t_idx idx)
{
	int	ks_num;

	if (set_substr_arg(dest, src, idx.start, idx.end) == true)
	{
		if (idx.start > idx.end)
			ks_num = EPERM;
		else
			ks_num = errno;
		set_err_var_01(err, true, FATAL, ks_num);
		err->v.str = strerror(ks_num);
		log_hist_err(err);
		return (true);
	}
	return (false);
}
