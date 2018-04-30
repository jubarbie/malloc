/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:12:10 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 18:41:30 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

size_t		g_page_size;

t_block	*new_room(size_t size, t_block *prev, t_block *next)
{
	void	*p;
	size_t	blk_sz;

	blk_sz = block_size(size);
	blk_sz = (ALIGN(blk_sz, getpagesize()));
	p = mmap(NULL, blk_sz, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (p == NULL)
	{
		printf("Could not map %zu bytes: %s\n", size, strerror(errno));
		return (NULL);
	}
	set_b(p, size, 0);
	set_b_next(p, next);
	set_b_prev(p, prev);
	if (prev != NULL)
		set_b_next(prev, p);
	if (next != NULL)
		set_b_prev(next, p);
	return (p);
}

size_t	count_alloc_blocks(t_block *ptr)
{
	size_t	c;
	t_block	*p;

	c = 0;
	p = ptr;
	while (p != NULL)
	{
		if (get_b_alloc(p) == 1)
			c++;
		p = get_b_next(p);
	}
	return (c);
}

void	*payload(t_block *ptr)
{
	return (ptr + 1);
}

t_block	*split_block(t_block *start, size_t size)
{
	t_block	*new;

	if (block_size(size) > get_b_size(start))
		return (NULL);
	else if (size == get_b_size(start))
		return (set_b_alloc(start, 1));
	new = (t_block *)((char *)payload(start) + size);
	set_b(new, get_b_size(start) - block_size(size), 0);
	set_b(start, size, 1);
	set_b_next(start, new);
	set_b_prev(new, start);
	return start;
}

size_t	block_size(size_t size)
{
	return (size + sizeof(t_block));
}
