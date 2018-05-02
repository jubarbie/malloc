/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 20:36:14 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/02 17:33:12 by jubarbie         ###   ########.fr       */
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
