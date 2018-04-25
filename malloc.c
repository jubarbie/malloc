/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 15:44:43 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*g_mem_tiny;
void	*g_mem_small;
size_t	g_page_size;
char	g_malloc_init = 0;

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

static void		init_malloc(void)
{
	if (g_malloc_init == 0)
	{
		printf("Init malloc\n");
		g_page_size = getpagesize();
		g_mem_tiny = NULL;
		g_mem_tiny = add_room(g_mem_tiny, TINY_SIZE);
		g_malloc_init = 1;
	}
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

	init_malloc();
	room = g_mem_tiny;
	while (room != NULL)
	{
		p = malloc_in_room(room, size);
		if (p == NULL)
		{
			printf("Malloc failed\n");
			if (next_room(room) == NULL)
			{
				printf("Adding a room\n");
				add_room(g_mem_tiny, TINY_SIZE);
			}
			printf("Moving\n");
			room = next_room(room);
		}
		else
		{
			return (p);
		}
	}
	return (NULL);
}
