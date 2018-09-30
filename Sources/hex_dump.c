/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 10:43:43 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/24 19:10:42 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

static void	print_hex_bit(unsigned char bit)
{
	char	str[3];
	char	base[17];
	int		i;
	int		nb;

	ft_strcpy(str, "00");
	ft_strcpy(base, "0123456789ABCDEF");
	i = 1;
	nb = (int)bit;
	while (bit != 0)
	{
		str[i--] = base[bit % 16];
		bit /= 16;
	}
	ft_putstr(str);
}

static void	print_char_bits(char *bit, size_t size)
{
	size_t	i;

	i = 0;
	ft_putchar(' ');
	while (i < size)
	{
		if (ft_isprint((unsigned char)*(bit + i)))
			ft_putchar((unsigned char)*(bit + i));
		else
			ft_putchar('.');
		i++;
	}
	ft_putchar('\n');
}

void		print_hex_dump(t_block *b)
{
	size_t	size;
	void	*ptr;
	size_t	i;

	i = 0;
	size = get_b_size(b);
	ptr = payload_addr(b);
	while (i < size)
	{
		if (i % 16 == 0)
		{
			(is_b_alloc(b)) ? ft_putstr("\t\033[31m") : ft_putstr("\t\033[32m");
			print_addr((void *)((char *)ptr + i), 1);
			ft_putstr("\033[0m");
			ft_putstr("  ");
		}
		print_hex_bit((unsigned char)*((char *)ptr + i));
		i++;
		ft_putchar(' ');
		if (i % 8 == 0)
			ft_putchar(' ');
		if (i % 16 == 0)
			print_char_bits(((char *)ptr + (((i - 1) / 16) * 16)), 16);
	}
}
