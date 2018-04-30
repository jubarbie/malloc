/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 19:15:57 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_mem	g_mem = { .tiny = NULL, .small = NULL, .medium = NULL };

static t_block		*malloc_in_mem(t_block *mem, size_t mem_size, size_t size)
{
	t_block	*block;
	t_block	*prev;

	block = mem;
	prev = block;
	while (block != NULL)
	{
		if (get_b_alloc(block) == 0 && block_size(size) <= get_b_size(block))
			return (split_block(block, size));
		prev = block;
		block = get_b_next(block);
	}
	if (block == NULL)
		block = new_room(mem_size, prev, NULL);
	return (split_block(block, size));
}

void			*ft_malloc(size_t size)
{
	void			*mem;
	size_t			r_size;

	if (size <= TINY_MAX)
	{
		r_size = TINY_SIZE;
		if (g_mem.tiny == NULL)
			g_mem.tiny = new_room(r_size, NULL, NULL);
		mem = g_mem.tiny;
	}
	else if (size <= SMALL_MAX)
	{
		r_size = SMALL_SIZE;
		if (g_mem.small == NULL)
			g_mem.small = new_room(r_size, NULL, NULL);
		mem = g_mem.small;
	}
	else
	{
		r_size = size;
		if (g_mem.medium == NULL)
			g_mem.medium = new_room(r_size, NULL, NULL);
		mem = g_mem.medium;

	}
	return (payload(malloc_in_mem(mem, r_size, size)));
}
