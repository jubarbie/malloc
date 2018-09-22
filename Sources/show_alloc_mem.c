/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:34:51 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/06 15:03:02 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static void		print_payload_line(t_block *p)
{
	if (p != NULL)
	{
		print_addr(payload_addr(p));
		ft_putstr(" - ");
		print_addr((void *)((char *)payload_addr(p) + get_b_size(p) - 1));
		ft_putstr(" : ");
		ft_putulnbr(get_b_size(p));
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
	if (p == NULL)
		return (0);
	if (getenv("MALLOC_DETAILS"))
	{
		if (is_b_first(p))
			ft_putstr(".");
		else
			ft_putstr(" ");
		(is_b_alloc(p)) ? ft_putstr("\033[31m") : ft_putstr("\033[32m");
		print_addr(p);
		ft_putstr("\n\t<- ");
		print_addr(get_b_prev(p));
		ft_putstr("\n\t-> ");
		print_addr(get_b_next(p));
		ft_putstr("\n\t");
	}
	if (is_b_alloc(p) || getenv("MALLOC_DETAILS"))
		print_payload_line(p);
	ft_putstr("\033[0m");
	s += (is_b_alloc(p)) ? get_b_size(p) : 0;
	return (s);
}

static void		print_total(size_t nb)
{
	ft_putstr("Total : ");
	ft_putulnbr(nb);
	ft_putendl(" octets\n");
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
	print_total(s);
	return (s);
}

void			print_addr(void *ptr)
{
	char	*addr;

	addr = ft_ptoa(ptr);
	if (addr != NULL)
	{
		ft_putstr(addr);
		free(addr);
	}
}

void			show_alloc_mem(void)
{
	size_t	s;

	s = 0;
	s += print_mem(g_mem.tiny, "TINY");
	s += print_mem(g_mem.small, "SMALL");
	s += print_mem(g_mem.medium, "LARGE");
	print_total(s);
}
