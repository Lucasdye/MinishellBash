/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:16:01 by jveuille          #+#    #+#             */
/*   Updated: 2022/11/10 18:16:10 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elcount, size_t elsize)
{
	void	*pstr;

	if (elsize > 0 && (SIZE_MAX / elsize) < elcount)
		return (NULL);
	pstr = malloc(elcount * elsize);
	if (!pstr)
		return (NULL);
	ft_memset(pstr, 0, elcount * elsize);
	return (pstr);
}
