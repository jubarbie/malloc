/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 11:24:04 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/04 11:09:22 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*new_alloc(t_block *old, size_t size)
{
	void	*new;

	new = malloc(size);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, payload(old), get_b_size(old));
	free(payload(old));
	return (new);
}

static t_block	*grow_block(t_block *block, t_block *next, size_t size)
{
	t_block	*new;
	size_t	s;

	s = block_size(get_b_size(next)) + get_b_size(block);
	set_b_size(block, size);
	new = (t_block *)((char *)payload(block) + size);
	set_b_size(new, s - block_size(size));
	set_b_next(new, get_b_next(next));
	set_b_prev(new, block);
	set_b_prev(get_b_next(next), new);
	set_b_next(block, new);
	return (block);
}

static t_block	*fusion_blocks(t_block *block, t_block *next, size_t size)
{
	set_b_next(block, get_b_next(next));
	set_b_prev(get_b_next(next), block);
	return (set_b_size(block, size));
}

void			*realloc(void *ptr, size_t size)
{
	t_block	*block;
	t_block	*next;
	size_t	s;

	if (ptr == NULL)
		return (malloc(size));
	block = find_block(ptr);
	if (block == NULL)
		return (NULL);
	if (get_b_size(block) >= size)
		return (split_block(block, size));
	next = get_b_next(block);
	if (next == NULL)
		return (new_alloc(block, size));
	if (b_cont(block, next) == 0)
		return (new_alloc(block, size));
	s = block_size(get_b_size(next)) + get_b_size(block);
	if (s < size)
		return (new_alloc(block, size));
	if (s == size)
		return (fusion_blocks(block, next, size));
	return (grow_block(block, next, size));
}
