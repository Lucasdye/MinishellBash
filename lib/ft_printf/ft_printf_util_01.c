/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:00:51 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/26 16:41:19 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strcat(char *dest, char *src)
{
	register int	i;
	register int	j;

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

static t_chk_spec	ft_srchstr(char str, char *wtab)
{
	t_chk_spec		t_chk;
	register int	i;

	i = 0;
	while (wtab[i] != '\0')
	{
		if (str == wtab[i])
		{
			t_chk.kstate = TRUE;
			t_chk.idx_tab = i;
			return (t_chk);
		}
		i++;
	}
	t_chk.kstate = FALSE;
	return (t_chk);
}

char	*ft_rev_char_tab(char *tab, int size)
{
	char			c;
	register int	i;

	i = 0;
	while (i <= (size / 2) - 1)
	{
		c = tab[i];
		tab[i] = tab[size - i - 1];
		tab[size - i - 1] = c;
		i++;
	}
	return (tab);
}

t_chk_spec	ft_spec_conv(char str)
{
	t_chk_spec	t_chk;
	char		*wtab;

	wtab = "cspdiuxX%";
	t_chk = ft_srchstr(str, wtab);
	return (t_chk);
}

char	ft_spec_flag(char str)
{
	t_chk_spec	t_chk;
	char		*wtab;

	wtab = "#-+\x20\x30";
	t_chk = ft_srchstr(str, wtab);
	return (t_chk.kstate);
}
