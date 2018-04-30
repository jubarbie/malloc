/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:34:51 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 12:43:37 by jubarbie         ###   ########.fr       */
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
		printf("%p - %p : %zu octets\n", hdb(p), (char *)hdb(p) + hdb_size(p),
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
	printf("%s : ", name);
	if (ptr != NULL)
	{
		printf("%p\n", get_hd_room(ptr));
		while(room)
		{	
			s += print_room(room);		
			room = next_room(room);
			printf("------------------\n");
		}
	}
	else
	{
		printf("NULL\n");
	}
	return (s);
}

void			show_alloc_mem(void)
{
	size_t	s;

	s = 0;
	s += print_mem(g_mem->tiny, "TINY");
	s += print_mem(g_mem->small, "SMALL");
	s += print_mem(g_mem->medium, "LARGE");
	printf("Total : %zu octets\n", s);
}
