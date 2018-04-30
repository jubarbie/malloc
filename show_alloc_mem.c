/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:34:51 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 19:17:30 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	print_block(t_block *p)
{
	size_t	s;

	s = 0;
	printf("[%d]%p : %zu octets\n", get_b_alloc(p), p, get_b_size(p));
	if (get_b_alloc(p) == 1)
	{
		s += get_b_size(p);
	}
	//printf("\t-> %p\n\t<- %p\n", get_b_next(p), get_b_prev(p));
	return (s);
}

static size_t	print_mem(t_block *ptr, char *name)
{
	size_t	s;
	t_block	*block;

	s = 0;
	printf("%s : ", name);
	if (ptr != NULL)	
	{
		block = ptr;
		printf("%p\n", ptr);
		while (block != NULL)
		{
			s += print_block(block);
			block = get_b_next(block);
		}
	}
	else
		printf("NULL\n");
	return (s);
}

void			show_alloc_mem(void)
{
	size_t	s;

	s = 0;
	s += print_mem(g_mem.tiny, "TINY");
	s += print_mem(g_mem.small, "SMALL");
	s += print_mem(g_mem.medium, "LARGE");
	printf("Total : %zu octets\n", s);
}
