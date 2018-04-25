/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:34:51 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 15:39:55 by jubarbie         ###   ########.fr       */
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

static void		print_room(void *room)
{	
	void	*p;
	
	printf("TINY : %p - %p : %lu bytes\n", room, room_limit(room), room_size(room));
	p = room;
	while ((char *)p < (char *)room_limit(room))
	{
		print_block(p);
		p = next_block(p);
	}
}

void			show_alloc_mem(void)
{
	void	*p;
	int		i;

	i = 0;
	printf("----- Memory viewer -----\n");
	p = g_mem_tiny;
	while(p)
	{
		printf("%d ", i);
		print_room(p);
		p = next_room(p);
		i++;
	}
}
