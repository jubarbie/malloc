/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:34:51 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/26 18:50:57 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		print_block(void *p)
{
	if (p == NULL)
		ft_putendl("Attempt to print NULL block");
	else
		printf("[%zu|%d] %zu bytes [%zu] %p\n", hdb_size(p), hdb_alloc(p),
				payload_size(p), ftb_size(p), p);
}

static void		print_room(void *room, int i, char *name)
{
	void	*block;

	printf("%d ", i);
	printf("%s : %p - %p : %lu bytes\n", name, room, room_limit(room), room_size(room));
	block = room;
	while ((char *)block < (char *)room_limit(room))
	{
		print_block(block);
		block = next_block(block);
	}
}

static void		print_mem(void *ptr, char *name)
{
	void	*room;
	int		i;
	
	i = 0;
	room = ptr;
	while(room != NULL)
	{	
		print_room(room, i, name);		
		room = next_room(room);
		i++;
	}
}

void			show_alloc_mem(void)
{
	ft_putendl("----- Memory viewer -----");
	print_mem(g_mem_tiny, "TINY");
	print_mem(g_mem_small, "SMALL");
	print_mem(g_mem_medium, "MEDIUM");
}
