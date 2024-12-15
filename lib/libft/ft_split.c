/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:54:30 by jveuille          #+#    #+#             */
/*   Updated: 2023/09/09 15:55:25 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_substr(char **str, register size_t nbstr)
{
	register size_t	i;

	i = 0;
	while (i <= nbstr)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static size_t	ft_substr_count(char const *str, register char sep)
{
	register size_t	nb_substr;
	register size_t	i;

	nb_substr = 0;
	i = 0;
	if (str[i] != sep && str[i] != '\0')
		nb_substr += 1;
	while (str[i] != '\0')
	{
		while (str[i] == sep && str[i + 1] == sep)
				i++;
		if (str[i] == sep && str[i + 1] != sep && str[i + 1] != '\0')
		{
				nb_substr += 1;
				i++;
		}
		i++;
	}
	return (nb_substr);
}

static size_t	ft_len_str(char const *str, register char sep)
{
	register size_t	i;
	register size_t	len_str;

	len_str = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sep)
			return (len_str);
		len_str++;
		i++;
	}	
	return (len_str);
}

static	char	**ft_char_trim(char **substr, char const *str, register char sep
	, register size_t nb_substr)
{
	register size_t	i;
	register size_t	j;
	register size_t	len_substr;

	i = 0;
	j = 0;
	while (i < nb_substr)
	{
		while (str[j] != '\0' && *str == sep)
			str++;
		len_substr = ft_len_str(str, sep);
		substr[i] = (char *)malloc(sizeof (**substr) *(len_substr + 1));
		if (substr[i] == NULL)
		{
			ft_free_substr(substr, i);
			return (NULL);
		}
		ft_strlcpy(substr[i], str, len_substr);
		str += len_substr;
		i++;
	}
	substr[i] = 0;
	return (substr);
}

char	**ft_split(char const *s, char c)
{
	char			**substr;
	register size_t	nb_substr;

	if (!s)
		return (NULL);
	nb_substr = ft_substr_count(s, c);
	substr = (char **)malloc(sizeof (*substr) * (nb_substr + 1));
	if (substr == NULL)
		return (NULL);
	substr = ft_char_trim(substr, s, c, nb_substr);
	return (substr);
}
