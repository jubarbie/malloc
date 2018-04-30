/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:29:48 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 11:48:23 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	defragment(void *min, void *max, void *ptr)
{
	size_t	size;

	while (prev_block(ptr) >= min && hdb_alloc(prev_block(ptr)) == 0)
	{
		ptr = prev_block(ptr);
		if (ptr == min)
		{
			break ;
		}
	}
	while (next_block(ptr) < max && hdb_alloc(next_block(ptr)) == 0)
	{
		size = hdb_size(ptr) + hdb_size(next_block(ptr));
		set_hdb(ptr, size, 0);
		set_ftb_size(ptr, size);
	}
}

/*
static int		count_rooms(void *ptr)
{
	void	*p;
	int		i;

	p = ptr;
	i = 1;
	if (p == NULL)
		return (0);
	while (next_room(p) != NULL)
	{
		i++;
	}
	return (i);
}*/

static void	*unalloc_block(void *room, void *block)
{
	void	*nav;

	nav = room;
	while ((char *)nav < (char *)room_limit(room))
	{
		if (nav == block && hdb_alloc(block) == 1)
		{
			set_hdb_alloc(block, 0);
			defragment(room, room_limit(room), block);
			break ;
		}
		nav = next_block(nav);
	}
	if ((char *)nav >= (char *)room_limit(room))
	{
		printf("Error: Trying to free pointer that was not allocated\n");
		return (NULL);
	}
	return (block);
}

static void *free_block(void *block, void *mem)
{
	void	*p;
	void	*prev;

	p = mem;
	prev = NULL;
	while (p != NULL)
	{
		if (block >= p && block <= room_limit(p))
		{
			if (unalloc_block(p, block) != NULL && count_alloc_blocks(p) == 0)
			{
				if (mem == g_mem->medium)
				{
					if (prev != NULL)
						get_hd_room(prev)->next = next_room(block);
					else
						mem = next_room(p);
					munmap((void *)get_hd_room(p), room_size(p));
					p = NULL;
				}
			}
			return (mem);
		}
		prev = p;
		p = next_room(p);
	}
	return (mem);
}

void	ft_free(void *ptr)
{	
	if (g_mem != NULL)
	{
		g_mem->tiny = free_block(ptr, g_mem->tiny);
		g_mem->small = free_block(ptr, g_mem->small);
		g_mem->medium = free_block(ptr, g_mem->medium);

	}
}
