/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/06 13:57:00 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_mem	g_mem = { .tiny = NULL, .small = NULL, .medium = NULL, .option = 0 };

t_block	*new_room(size_t size, t_block *prev, t_block *next)
{
	void	*b;
	size_t	bsize;

	bsize = block_size(size);
	b = mmap(NULL, bsize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (b == NULL)
		return (NULL);
	b = init_block(b);
	set_b_all(b, size, 1, 0);
	attach_block(b, prev, next);
	return (b);
}

static t_block	*malloc_in_mem(t_block *mem, size_t mem_size, size_t size)
{
	t_block	*block;
	t_block	*prev;

	block = mem;
	prev = block;
	while (block != NULL)
	{
		if (!is_b_alloc(block) && size == get_b_size(block))
			return (set_b_alloc(block));
		if (!is_b_alloc(block) && block_size(size) <= get_b_size(block))
			return (split_block(block, size));
		prev = block;
		block = get_b_next(block);
	}
	if (block == NULL)
	{
		block = new_room(mem_size, prev, NULL);
		if (size == get_b_size(block))
			return (set_b_alloc(block));
	}
	return (split_block(block, size));
}

/*
** Initialize memory by creating a new room
** Allocate the memory
*/
static void		*init_and_alloc(void **mem, size_t mem_size, size_t size)
{
	t_block	*b;

	if (*mem == NULL)
		*mem = (void *)new_room(mem_size, NULL, NULL);
	b = malloc_in_mem((t_block *)(*mem), mem_size, size);
	if (b == NULL)
		return (NULL);
	return (b);
}
 /*
 ** Return the appropriate memory address
 */
void			*dispatch_alloc(size_t size)
{
	size_t	alsize;

	alsize = ALIGN(size, 16);
	if (alsize <= TINY_MAX)
		return (init_and_alloc(&(g_mem.tiny), TINY_SIZE, alsize));
	else if (alsize <= SMALL_MAX)
		return (init_and_alloc(&(g_mem.small), SMALL_SIZE, alsize));
	else
		return (init_and_alloc(&(g_mem.medium), alsize, alsize));
}

void			*malloc(size_t size)
{
	void	*block;

	if (size == 0)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	block = dispatch_alloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (payload_addr(block));
}
