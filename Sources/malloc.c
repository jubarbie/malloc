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

t_mem	g_mem = { .tiny = NULL, .small = NULL, .medium = NULL, .options = 0 };

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

t_block			*dispatch_alloc(size_t size)
{
	size_t	alsize;

	alsize = align_16(size);
	if (alsize == 0)
		return (NULL);
	if (alsize <= TINY)
		return (init_and_alloc(&(g_mem.tiny), block_size(TINY) * 110, alsize));
	else if (alsize <= SMALL)
		return (init_and_alloc(&(g_mem.small), block_size(SMALL) * 110,
																	alsize));
	else
		return (init_and_alloc(&(g_mem.medium), alsize, alsize));
}

void			*pthsafe_malloc(size_t size)
{
	t_block	*block;
	void	*ptr;

	init_options();
	debug_malloc(size);
	if (size == 0)
		return (NULL);
	block = dispatch_alloc(size);
	ptr = payload_addr(block);
	if (ptr == NULL)
		errno = ENOMEM;
	debug_block(block);
	return (ptr);
}

void			*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = pthsafe_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
