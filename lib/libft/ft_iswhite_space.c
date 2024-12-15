/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhite_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:31:59 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 10:32:09 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iswhite_space(char str)
{
	char			*wtab;
	register int	i;

	wtab = "\x20\t\n\v\f\r";
	i = 0;
	while (wtab[i] != '\0')
	{
		if (str == wtab[i])
		{
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
