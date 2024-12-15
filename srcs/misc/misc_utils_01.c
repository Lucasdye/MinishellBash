/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:44:03 by jveuille          #+#    #+#             */
/*   Updated: 2023/09/30 10:05:47 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_strchk(char *s1, char *s2)
{
	register size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	while (s1[i] != '\0' && s2[i] != '\0')
	{	
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}

char	*ft_strstr(char *str, char *to_find)
{
	register char	ks_chk;
	register size_t	i;
	register size_t	j;

	i = 0;
	while (str[i] != '\0')
	{
		ks_chk = true;
		j = 0;
		while (to_find[j] != '\0' && to_find[j] != str[i])
		{	
			ks_chk = false;
			j++;
		}
		i++;
	}
	if (ks_chk == true)
	{
		return (&str[i]);
	}
	return (NULL);
}

t_bool	chk_strstr(char *str, char *set)
{
	register size_t	i;
	register size_t	len_s;

	len_s = ft_strlen(set);
	if (!(str && set) || (ft_strlen(str) < len_s))
		return (false);
	i = 0;
	while (str[i + len_s] != '\0')
	{
		if (!(ft_strncmp(str, set, len_s)))
			return (true);
		i++;
	}
	return (false);
}

char	*ft_strcat_m(char *dest, char *src)
{
	register size_t	i;
	register size_t	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_m(char *s1, char *s2)
{
	register size_t	len_s1;
	register size_t	len_s2;
	char			*str;

	if (s1 || s2)
	{
		if (!s1)
			return ((char *)s2);
		if (!s2)
			return ((char *)s1);
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		str = (char *)calloc((len_s1 + len_s2 + 1), sizeof (char));
		if (str != NULL)
		{
			ft_strcat_m(str, s1);
			free (s1);
			ft_strcat_m(str, s2);
			return (str);
		}
	}
	return (NULL);
}
