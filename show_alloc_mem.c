/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:34:51 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/26 14:34:58 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		print_block(void *p)
{
	if (p == NULL)
	{
		printf("Attempt to print NULL block");
	}
	else
	{
		printf("[%zu|%d] %zu bytes [%zu] %p\n", hdb_size(p), hdb_alloc(p),
				payload_size(p), ftb_size(p), p);
	}
}

static void		print_room(void *room, char *name)
{	
	void	*block;
	void	*p;
	int		i;
	
	i = 0;
	p = room;
	while(p != NULL)
	{
		printf("%d ", i);
		printf("%s : %p - %p : %lu bytes\n", name, room, room_limit(room), room_size(room));
		block = room;
		while ((char *)block < (char *)room_limit(room))
		{
			print_block(block);
			block = next_block(block);
		}
		p = next_room(p);
		i++;
	}
}

void			show_alloc_mem(void)
{
	printf("----- Memory viewer -----\n");
	print_room(g_mem_tiny, "TINY");
	print_room(g_mem_small, "SMALL");
	print_room(g_mem_medium, "MEDIUM");
}
