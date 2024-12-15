/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:02:38 by jveuille          #+#    #+#             */
/*   Updated: 2022/09/28 12:02:46 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_inv_putstr(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		write(1, &str[i], 1);
		i--;
	}
}

int	ft_calc_base_10(char *str, int nbr)
{
	int	mod;
	int	i;

	i = 0;
	while (nbr != 0)
	{
		mod = nbr % 10;
		str[i] = mod + 48;
		nbr = nbr / 10 ;
		i++;
	}
	str[i] = '\0';
	return (nbr);
}

void	ft_putnbr(int nb)
{
	char	str[11];

	if (nb == 0)
	{
		ft_putstr("0");
		return ;
	}
	else if (nb == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	else if (nb < 0)
	{
		ft_putstr("-");
		nb = -1 * nb;
	}
	ft_calc_base_10(str, nb);
	ft_inv_putstr(str);
}
