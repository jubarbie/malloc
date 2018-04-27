/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:34:51 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/27 17:53:23 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	print_block(void *p)
{
	size_t	s;

	s = 0;
	if (hdb_alloc(p) == 1)
	{
		s += hdb_size(p);
		printf("%p - %p : %zu octetcs\n", hdb(p), (char *)hdb(p) + hdb_size(p),
				payload_size(p));
	}
	return (s);
}

static size_t	print_room(void *room)
{
	void	*block;
	size_t	s;

	s = 0;
	block = room;
	while ((char *)block < (char *)room_limit(room))
	{
		s += print_block(block);
		block = next_block(block);
	}
	return (s);
}

static size_t	print_mem(void *ptr, char *name)
{
	void	*room;
	size_t	s;

	s = 0;
	room = ptr;
	if (ptr != NULL)
	{
		printf("%s : %p\n", name, get_hd_room(ptr));
		while(room)
		{	
			s += print_room(room);		
			room = next_room(room);
		}
	}
	return (s);
}

void			show_alloc_mem(void)
{
	size_t	s;

	s = 0;
	s += print_mem(g_mem_tiny, "TINY");
	s += print_mem(g_mem_small, "SMALL");
	s += print_mem(g_mem_medium, "LARGE");
	printf("Total : %zu octets\n", s);
}
