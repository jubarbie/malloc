/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 15:09:50 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/04 16:00:16 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long int	ft_power_long(unsigned long int n, int power)
{
	unsigned long int res;

	res = n * n;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (n);
	if (power > 2)
		res = n * (ft_power_long(n, --power));
	return (res);
}

static int	ft_nbrlen(unsigned long int nb, int base)
{
	int i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= base;
		i++;
	}
	return (i);
}

static unsigned long int	ft_to_dec(char *nbr, char *base)
{
	unsigned long int	nbr_dec;
	int					len_base;
	int					len_nbr;
	int					i;
	int					j;

	len_base = ft_strlen(base);
	len_nbr = ft_strlen(nbr);
	nbr_dec = 0;
	i = -1;
	while (++i < len_nbr)
	{
		j = -1;
		while (++j < len_base)
			if (nbr[i] == base[j])
				nbr_dec = nbr_dec + (j * ft_power_long(len_base, len_nbr - i - 1));
	}
	return (nbr_dec);
}

char					*ft_convert_base(char *nbr, char *bf, char *bt)
{
	char				*ret;
	unsigned long int	nb_dec;
	int					i;
	int					b;
	int					m;

	nb_dec = ft_to_dec(nbr, bf);
	b = ft_strlen(bt);
	i = ft_nbrlen(nb_dec, b);
	ret = ft_strnew(i);
	if (ret == NULL)
		return (NULL);
	while (--i >= 0)
	{
		m = nb_dec % b;
		ret[i] = bt[m];
		nb_dec /= b;
	}
	return (ret);
}
