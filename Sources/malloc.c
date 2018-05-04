/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/04 20:06:21 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_mem	g_mem = { .tiny = NULL, .small = NULL, .medium = NULL, .option = 0 };

static void		get_options(void)
{
	if (getenv("MallocVerbose") != NULL)
		g_mem.option |= (1 << 1);
}

static t_block	*malloc_in_mem(t_block *mem, size_t mem_size, size_t size)
{
	t_block	*block;
	t_block	*prev;

	block = mem;
	prev = block;
	while (block != NULL)
	{
		if (get_b_alloc(block) == 0 && size == get_b_size(block))
			return (set_b_alloc(block, 1));
		if (get_b_alloc(block) == 0 && block_size(size) <= get_b_size(block))
			return (split_block(block, size));
		prev = block;
		block = get_b_next(block);
	}
	if (block == NULL)
	{
		block = new_room(mem_size, prev, NULL);
		if (size == get_b_size(block))
			return (set_b_alloc(block, 1));
	}
	return (split_block(block, size));
}

static void		*init_mem(void **mem, size_t mem_size, size_t size)
{
	t_block	*b;

	if (*mem == NULL)
		*mem = (void *)new_room(mem_size, NULL, NULL);
	b = malloc_in_mem((t_block *)(*mem), mem_size, size);
	if (b == NULL)
		return (NULL);
	return (payload(b));
}

static void		*dispatch_mem(size_t size)
{
	if (size == 0)
		return (NULL);
	if (size <= TINY_MAX)
		return (init_mem(&(g_mem.tiny), TINY_SIZE, size));
	else if (size <= SMALL_MAX)
		return (init_mem(&(g_mem.small), SMALL_SIZE, size));
	else
		return (init_mem(&(g_mem.medium), size, size));
}

void			*malloc(size_t size)
{
	void	*addr;

	if (!(g_mem.option & (1 << 0)))
		get_options();
	pthread_mutex_lock(&g_mutex);
	addr = dispatch_mem(size);
	pthread_mutex_unlock(&g_mutex);
	g_mem.option |= (1 << 0);
	return (addr);
}
