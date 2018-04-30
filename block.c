/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:12:10 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 12:40:12 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"
#include "room.h"

size_t	count_alloc_blocks(void *ptr)
{
	size_t	c;
	void	*p;
	void	*limit;

	c = 0;
	p = ptr;
	limit = room_limit(ptr);
	while (p < limit)
	{
		if (hdb_alloc(p) == 1)
			c++;
		p = next_block(p);
	}
	return (c);
}

void	split_block(void *start, size_t size)
{
	void	*new;

	new = (char *)start + size;
	set_hdb(new, hdb_size(start) - size, 0);
	set_ftb_size(new, hdb_size(start) - size);
	set_hdb(start, size, 1);
	set_ftb_size(start, size);
}

void	*next_block(void *ptr)
{
	return ((char *)ptr + hdb_size(ptr));
}

void	*prev_block(void *ptr)
{
	size_t	size;
	size_t	*ft;

	ft = (size_t *)hdb(ptr) - 1;
	size = *ft - sizeof(t_hdb) - sizeof(size_t);
	return ((char *)ft - size);
}

size_t	block_size(size_t size)
{
	return (size + sizeof(t_hdb) + sizeof(size_t));
}

size_t	payload_size(void *p)
{
	return (hdb_size(p) - sizeof(t_hdb) - sizeof(size_t));
}
