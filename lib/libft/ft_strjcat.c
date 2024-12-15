/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 08:26:37 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/17 08:23:27 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_strjcat(char **dst, char *src)
{
	register size_t	len_s;
	char			*s_tmp;

	if (*dst == NULL)
	{
		len_s = ft_strlen(src);
		*dst = ft_calloc((len_s + 1), sizeof(char));
		if (*dst == NULL)
			return (true);
		ft_strlcat(*dst, src, (len_s + 1));
	}
	else
	{
		s_tmp = strdup(*dst);
		if (s_tmp == NULL)
			return (true);
		free(*dst);
		*dst = ft_strjoin(s_tmp, src);
		free(s_tmp);
		if (*dst == NULL)
			return (true);
	}
	return (false);
}
