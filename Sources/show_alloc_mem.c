/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:34:51 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/02 21:04:32 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		print_addr(void *ptr)
{
	char	*s1;
	char	*s2;

	if (ptr == NULL)
		ft_putstr("0x0");
	else
	{
		s1 = ft_itoa((unsigned int)ptr);
		if (s1 != NULL)
		{
			s2 = ft_convert_base(s1, "0123456789", "0123456789abcdef");
			if (s2 != NULL)
			{
				ft_putstr("0x10");
				ft_putstr(s2);
				free(s2);
			}
			free(s1);
		}
	}
}

static void		print_payload_line(t_block *p)
{
	if (p != NULL)
	{
		print_addr(payload(p));
		ft_putstr(" - ");
		print_addr((void *)((char *)payload(p) + get_b_size(p) - 1));
		ft_putstr(" : ");
		ft_putnbr((int)get_b_size(p));
		ft_putendl(" octets");
	}
	else
	{
		ft_putstr("PAYLOAD NULL");
	}
}

static size_t	print_block(t_block *p)
{
	size_t	s;

	s = 0;
	if (p != NULL)
	{
		if (g_mem.option == 1)
		{
			(get_b_alloc(p) == 1) ? ft_putstr("\033[31m") : ft_putstr("\033[32m");
			print_addr(p);
			ft_putstr("\n\t<- ");
			print_addr(get_b_prev(p));
			ft_putstr("\n\t-> ");
			print_addr(get_b_next(p));
			ft_putstr("\n\t");
		}
		if (get_b_alloc(p) == 1)
			s += get_b_size(p);
		print_payload_line(p);
		if (g_mem.option == 1)
			ft_putstr("\033[0m");
	}
	else
	{
		ft_putstr("PRINT BLOCK NULL");
	}
	return (s);
}

static size_t	print_mem(t_block *ptr, char *name)
{
	size_t	s;
	t_block	*block;

	s = 0;
	ft_putstr(name);
	ft_putstr(" : ");
	print_addr(ptr);
	ft_putchar('\n');
	block = ptr;
	while (block != NULL)
	{
		s += print_block(block);
		block = get_b_next(block);
	}
	return (s);
}

void			show_alloc_mem(void)
{
	size_t	s;

	s = 0;
	s += print_mem(g_mem.tiny, "TINY");
	s += print_mem(g_mem.small, "SMALL");
	s += print_mem(g_mem.medium, "LARGE");
	ft_putstr("Total : ");
	ft_putnbr((int)s);
	ft_putendl(" octets\n");
}
