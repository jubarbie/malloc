/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:29:48 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 18:31:10 by jubarbie         ###   ########.fr       */
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

static void	*find_room(void *ptr)
{
	void	*p;

	p = g_mem_tiny;
	while (p != NULL)
	{
		if (ptr >= p && ptr <= room_limit(p))
			return (p);
		p = next_room(p);
	}
	p = g_mem_small;
	while (p != NULL)
	{
		if (ptr >= p && ptr <= room_limit(p))
			return (p);
		p = next_room(p);
	}
	return (NULL);
}

void		ft_free(void *ptr)
{
	void	*block;
	void	*room;
	
	room = find_room(ptr);
	block = room;
	while ((char *)block < (char *)room_limit(room))
	{
		if (block == ptr && hdb_alloc(ptr) == 1)
		{
			set_hdb_alloc(ptr, 0);
			defragment(room, room_limit(room), ptr);
			break ;
		}
		block = next_block(block);
	}
	if ((char *)block >= (char *)room_limit(room))
	{
		printf("Error: Trying to free pointer that was not allocated\n");
	}
}
