/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 20:36:14 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/24 17:57:47 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	char	*nbr;

	nbr = ft_itoa(n);
	if (nbr != NULL)
	{
		ft_putstr(nbr);
		free(nbr);
		nbr = NULL;
	}
	else
	{
		ft_putstr("itoa failed");
	}
}

void	ft_putulnbr(unsigned long int n)
{
	char	*nbr;

	nbr = ft_sizetoa(n);
	if (nbr != NULL)
	{
		ft_putstr(nbr);
		free(nbr);
	}
	else
	{
		ft_putstr("sizetoa failed");
	}
}
