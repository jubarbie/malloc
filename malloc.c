/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 12:05:08 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_mem	*g_mem = NULL;

static void		*add_room(void *first, size_t size)
{
	t_hd_room	*p;

	if (first == NULL)
	{
		first = new_room(size);
		return (first);
	}
	p = first;
	while (next_room(p) != NULL)
	{
		p = next_room(p);
	}
	get_hd_room(p)->next = new_room(size);
	return (get_hd_room(p)->next);
}

static t_mem		*init_malloc(t_mem *mem)
{
	size_t	s;

	s = (ALIGN(sizeof(t_mem), getpagesize()));
	if (mem == NULL)
	{
		mem = (t_mem *)mmap(NULL, s, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (mem != NULL)
		{
			mem->tiny = NULL;
			mem->small = NULL;
			mem->medium = NULL;
		}
	}
	return mem;
}

static void		*malloc_in_room(void *room, size_t size)
{
	void	*p;
	size_t	blk_sz;

	p = room;
	blk_sz = block_size(size);
	while ((hdb_alloc(p) == 1 || (hdb_alloc(p) == 0 && (blk_sz >
	payload_size(p)))) && (char *)p + blk_sz < (char *)room_limit(room))
	{
		p = next_block(p);
	}
	if ((char *)p + blk_sz > (char *)room_limit(room))
	{
		return (NULL);
	}
	if (blk_sz == hdb_size(p))
	{
		set_hdb_alloc(p, 1);
		return (p);
	}
	split_block(p, blk_sz);
	return (p);
}

void			*ft_malloc(size_t size)
{
	void	*p;
	void	*room;
	void	*first;
	size_t	r_size;
	
	g_mem = init_malloc(g_mem);
	if (size <= TINY_MAX)
	{
		r_size = TINY_SIZE;
		first = g_mem->tiny;
		if (g_mem->tiny == NULL)
		{
			g_mem->tiny = add_room(g_mem->tiny, r_size);
			return (malloc_in_room(g_mem->tiny, size));
		}
	}
	else if (size <= SMALL_MAX)
	{
		r_size = SMALL_SIZE;
		first = g_mem->small;
		if (g_mem->small == NULL)
		{
			g_mem->small = add_room(g_mem->small, r_size);
			return (malloc_in_room(g_mem->small, size));
		}
	}
	else 
	{
		room = add_room(g_mem->medium, size);
		if (g_mem->medium == NULL)
		{
			g_mem->medium = room;
		}
		return (malloc_in_room(room, size));
	}
	room = first;
	while (room != NULL)
	{
		p = malloc_in_room(room, size);
		if (p == NULL)
		{
			if (next_room(room) == NULL)
			{
				add_room(first, r_size);
			}
			room = next_room(room);
		}
		else
		{
			return (p);
		}
	}
	return (NULL);
}
