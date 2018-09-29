/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 18:17:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/24 20:45:40 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

static size_t	size_power(size_t n, int power)
{
	size_t res;

	res = n * n;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (n);
	if (power > 2)
		res = n * (size_power(n, --power));
	return (res);
}

void			print_addr(void *ptr)
{
	char				addr[11];
	char				base[17];
	unsigned long int	p;
	int					i;

	ft_strcpy(addr, "0x00000000");
	ft_strcpy(base, "0123456789ABCDEF");
	if (ptr == NULL)
		ft_putstr("(null)");
	else
	{
		i = 9;
		p = (unsigned long int)ptr;
		while (p != 0 && i > 1)
		{
			addr[i--] = base[p % 16];
			p /= 16;
		}
		ft_putstr(addr);
	}
}

void			print_size(size_t size)
{
	char	str[21];
	int		i;
	size_t	p;

	ft_strcpy(str, "00000000000000000000");
	if (size == 0)
		ft_putstr("0");
	i = 19;
	p = size_power(10, i);
	while (size % p != 0 && i >= 0)
	{
		str[19 - i] = (size / p) + 48;
		size %= p;
		i--;
		p = size_power(10, i);
	}
	str[19 - i] = (size / p) + 48;
	i = 0;
	while (str[i] == '0')
		i++;
	ft_putstr(&str[i]);
}
