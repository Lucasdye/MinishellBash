/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_04.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:46:12 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/10 20:29:51 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_tablen(char **tab)
{
	register int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

t_bool	ft_isvar_str(char *s)
{
	register size_t	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if ((ft_isalnum_var(s[i]) == false) && (s[i] != 36))
				return (false);
			i++;
		}
		if (i != 0)
			return (true);
	}
	return (false);
}

t_bool	ft_isnum_str(char *str)
{
	register size_t	i;

	i = 0;
	if (!str)
		return (false);
	if ((str[i] == PLUS) || (str[i] == MINUS))
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

t_bool	ft_get_info(t_data *dt, char **var, int fd)
{
	t_bool	ks;
	char	*s1;

	ks = false;
	s1 = NULL;
	*var = NULL;
	s1 = get_next_line(fd);
	if (s1 == NULL)
		*var = NULL;
	else
		*var = ft_substr(s1, 0, (ft_strlen(s1) - 1));
	if (*var == NULL)
	{
		set_err_std_01(&dt->err);
		log_hist_err(&dt->err);
		ks = true;
	}
	while (s1 != NULL)
	{
		free(s1);
		s1 = get_next_line(fd);
	}
	return (ks);
}
