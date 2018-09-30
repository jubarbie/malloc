/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/24 21:39:16 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

t_mem	g_mem = { .tiny = NULL, .small = NULL, .medium = NULL };

static t_block	*malloc_in_mem(t_block *mem, size_t mem_size, size_t size)
{
	t_block	*block;
	t_block	*prev;

	block = mem;
	prev = block;
	while (block != NULL)
	{
		if (!is_b_alloc(block) && is_fitting(block, size))
			return (set_b_alloc(block));
		if (!is_b_alloc(block) && is_splittable(block, size))
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

static t_block	*init_and_alloc(void **mem, size_t mem_size, size_t size)
{
	t_block	*b;

	if (*mem == NULL)
		*mem = (void *)new_room(mem_size, NULL, NULL);
	b = malloc_in_mem((t_block *)(*mem), mem_size, size);
	if (b == NULL)
		return (NULL);
	return (b);
}

t_block			*new_room(size_t size, t_block *prev, t_block *next)
{
	void	*b;
	size_t	bs;

	bs = align_page(block_size(size));
	b = mmap(NULL, bs, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (b == NULL)
		return (NULL);
	b = init_block(b);
	set_b_all(b, bs - sizeof(t_block), 1, 0);
	attach_block(b, prev, next);
	return (b);
}

t_block			*dispatch_alloc(size_t size)
{
	size_t	alsize;

	alsize = align_16(size);
	if (alsize == 0)
		return (NULL);
	if (alsize <= TINY)
		return (init_and_alloc(&(g_mem.tiny), block_size(TINY) * 50, alsize));
	else if (alsize <= SMALL)
		return (init_and_alloc(&(g_mem.small), block_size(SMALL) * 20, alsize));
	else
		return (init_and_alloc(&(g_mem.medium), alsize, alsize));
}

void			*malloc(size_t size)
{
	t_block	*block;
	void	*ptr;

	if (size == 0)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	block = dispatch_alloc(size);
	ptr = payload_addr(block);
	pthread_mutex_unlock(&g_mutex);
	if (ptr == NULL)
		errno = ENOMEM;
	return (ptr);
}
