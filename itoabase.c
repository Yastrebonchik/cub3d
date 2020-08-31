/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoabase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 23:06:14 by kcedra            #+#    #+#             */
/*   Updated: 2020/08/27 14:05:21 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char		symbol(long long int nb, char type)
{
	char	symbol;

	if (type == 'x')
		symbol = 32;
	else
		symbol = 0;
	if (nb % 16 < 10)
		return ((nb % 16) + 48);
	else if (nb % 16 == 10)
		return (symbol + 'A');
	else if (nb % 16 == 11)
		return (symbol + 'B');
	else if (nb % 16 == 12)
		return (symbol + 'C');
	else if (nb % 16 == 13)
		return (symbol + 'D');
	else if (nb % 16 == 14)
		return (symbol + 'E');
	else
		return (symbol + 'F');
}

char			*ft_itoabase(long long int nb, char type)
{
	int				len;
	long long int	copy;
	char			*s;

	copy = nb;
	len = 1;
	while (copy / 16 != 0)
	{
		copy = copy / 16;
		len++;
	}
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = '\0';
	while (len != 0)
	{
		len--;
		s[len] = symbol(nb, type);
		nb = nb / 16;
	}
	return (s);
}
