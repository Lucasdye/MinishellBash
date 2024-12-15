/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:16:00 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:29:16 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

void	ft_bzero(void *s, size_t n)
{
	register size_t	i;

	i = 0;
	if (s != 0)
	{
		while (i < n)
		{
			*(char *)(s + i) = '\0';
			i++;
		}
	}
}