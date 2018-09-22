/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 11:24:04 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/06 13:56:22 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static size_t	min_size(size_t s1, size_t s2)
{
	if (s1 < s2)
		return (s1);
	return (s2);
}

static void		*new_alloc(t_block *old, size_t size)
{
	void	*new;

	new = dispatch_alloc(size);
	if (new == NULL)
		return (NULL);
	ft_memcpy(payload_addr(new), payload_addr(old), min_size(get_b_size(new), get_b_size(old)));
	pthsafe_free(payload_addr(old));
	return (new);
}

static t_block	*grow_block(t_block *block, t_block *next, size_t size)
{
	t_block	*new;
	size_t	s;

	if (!b_cont(block, next) || is_b_first(next))
	{
		ft_putendl("grow not cont");
		return (NULL);
	}
	s = block_size(get_b_size(next)) + get_b_size(block);
	set_b_size(block, size);
	new = init_block((void *)((char *)payload_addr(block) + size));
	set_b_size(new, s - block_size(size));
	attach_block(new, block, get_b_next(next));
	return (block);
}

static void		*dispatch_realloc(void *ptr, size_t size)
{
	t_block	*block;
	t_block	*next;
	size_t	alsize;
	size_t	s;

	alsize = ALIGN(size, 16);
	block = find_block(ptr);
	if (block == NULL)
		return (NULL);
	if (!is_b_alloc(block))
		return (NULL);
	if (get_b_size(block) >= alsize && get_b_size(block) <= block_size(alsize))
		return (block);
	if (get_b_size(block) > block_size(alsize))
		return (split_block(block, alsize));
	next = get_b_next(block);
	if (!b_cont(block, next) || is_b_alloc(next) || is_b_first(next))
		return (new_alloc(block, alsize));
	s = get_b_size(next) + get_b_size(block);
	if (alsize > block_size(s))
		return (new_alloc(block, alsize));
	if (alsize == block_size(s) || block_size(alsize) == block_size(s))
		return (fusion_blocks(block, next));
	return (grow_block(block, next, alsize));
}

void			*realloc(void *ptr, size_t size)
{
	void	*block;

	pthread_mutex_lock(&g_mutex);
	if (ptr == NULL)
		return (payload_addr(dispatch_alloc(size)));
	if (ptr != NULL && size == 0)
	{
		pthsafe_free(ptr);
		return (NULL);
	}
	block = dispatch_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (payload_addr(block));
}
