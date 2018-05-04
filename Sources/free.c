/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:29:48 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/04 20:05:42 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		unmap_mem(t_block *first, t_block *block)
{
	if (block == first)
		g_mem.medium = get_b_next(block);
	if (get_b_prev(block) != NULL)
		set_b_next(get_b_prev(block), get_b_next(block));
	if (get_b_next(block) != NULL)
		set_b_prev(get_b_next(block), get_b_prev(block));
	munmap((void *)(block - 1), block_size(get_b_size(block)));
}

static t_block	*unalloc_block(void *ptr, t_block *first)
{
	t_block	*block;

	if (ptr == NULL || first == NULL)
		return (NULL);
	ptr = (t_block *)ptr - 1;
	block = first;
	while (block != NULL)
	{
		if (block == ptr && get_b_alloc(block) == 1)
		{
			if (first == (t_block *)g_mem.medium)
			{
				unmap_mem(first, block);
				return (ptr);
			}
			set_b_alloc(block, 0);
			return (defragment(block));
		}
		block = get_b_next(block);
	}
	return (NULL);
}

t_block			*defragment(t_block *ptr)
{
	size_t	size;

	while (get_b_prev(ptr) != NULL && get_b_alloc(get_b_prev(ptr)) == 0
			&& get_b_first(ptr) == 0)
		ptr = get_b_prev(ptr);
	while (get_b_next(ptr) != NULL && get_b_alloc(get_b_next(ptr)) == 0
			&& get_b_first(get_b_next(ptr)) == 0)
	{
		size = get_b_size(ptr) + block_size(get_b_size(get_b_next(ptr)));
		set_b_next(ptr, get_b_next(get_b_next(ptr)));
		set_b(ptr, size, 0);
	}
	if (get_b_next(ptr) != NULL)
		set_b_prev(get_b_next(ptr), ptr);
	return (ptr);
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	if (ptr != NULL && find_block(ptr) != NULL)
	{
		if (unalloc_block(ptr, (t_block *)g_mem.tiny) == NULL)
			if (unalloc_block(ptr, (t_block *)g_mem.small) == NULL)
				if (unalloc_block(ptr, (t_block *)g_mem.medium) == NULL)
					ft_putendl("Trying to free block that was not allocated");
	}
	pthread_mutex_unlock(&g_mutex);
}
