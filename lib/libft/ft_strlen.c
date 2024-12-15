/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:50:35 by jveuille          #+#    #+#             */
/*   Updated: 2023/09/22 15:22:03 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	register size_t	i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
