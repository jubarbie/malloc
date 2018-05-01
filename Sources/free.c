/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:29:48 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/01 21:25:13 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	t_block	*min;

	min = ptr;
	while (get_b_prev(min) != NULL && get_b_alloc(get_b_prev(min)) == 0
			&& b_cont(get_b_prev(min), min) == 1)
		min = get_b_prev(min);
	while (get_b_next(ptr) != NULL && get_b_alloc(get_b_next(ptr)) == 0
			&& b_cont(ptr, get_b_next(ptr)) == 1)
	{
		size = get_b_size(ptr) + block_size(get_b_size(get_b_next(ptr)));
		set_b_next(ptr, get_b_next(get_b_next(ptr)));
		set_b(ptr, size, 0);
	}
	if (get_b_next(ptr) != NULL)
		set_b_prev(get_b_next(ptr), ptr);
	return (ptr);
}

void			ft_free(void *ptr)
{
	if (g_mem.option == 1)
	{
		printf("freeing %p\n", ptr);
	}
	if (unalloc_block(ptr, (t_block *)g_mem.tiny) == NULL)
		if (unalloc_block(ptr, (t_block *)g_mem.small) == NULL)
			if (unalloc_block(ptr, (t_block *)g_mem.medium) == NULL)
				ft_putendl("Trying to free block that was not allocated");

}