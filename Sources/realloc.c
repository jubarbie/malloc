/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 11:24:04 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/24 21:38:55 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static size_t		min_size(size_t s1, size_t s2)
{
	if (s1 < s2)
		return (s1);
	return (s2);
}

static t_block		*new_alloc(t_block *old, size_t size)
{
	t_block	*new;

	new = dispatch_alloc(size);
	if (new == NULL || old == NULL)
		return (NULL);
	ft_memcpy(payload_addr(new), payload_addr(old),
				min_size(get_b_size(new), get_b_size(old)));
	pthsafe_free(payload_addr(old));
	return (new);
}

static t_block		*dispatch_realloc(void *ptr, size_t size)
{
	t_block	*block;
	t_block	*next;
	size_t	alsize;
	size_t	s;

	alsize = align_16(size);
	block = find_block(ptr);
	if (block == NULL)
		return (NULL);
	if (!is_b_alloc(block))
		return (NULL);
	if (is_fitting(block, alsize))
		return (block);
	if (is_splittable(block, alsize))
		return (block);
	next = get_b_next(block);
	if (!b_cont(block, next) || is_b_alloc(next) || is_b_first(next))
		return (new_alloc(block, alsize));
	s = block_size(get_b_size(next)) + get_b_size(block);
	if (alsize > s)
		return (new_alloc(block, alsize));
	if (s >= alsize && s <= alsize + block_size(align_16(1)))
		return (fusion_blocks(block, next));
	return (grow_block(block, next, alsize));
}

static void			*pthsafe_realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*ret;

	debug_realloc(ptr, size);
	if (ptr == NULL)
		block = dispatch_alloc(size);
	else if (size == 0)
	{
		pthsafe_free(ptr);
		block = dispatch_alloc(1);
	}
	else
		block = dispatch_realloc(ptr, size);
	ret = payload_addr(block);
	debug_block(block);
	if (ret == NULL)
		errno = ENOMEM;
	return (ret);
}

void				*realloc(void *ptr, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	ret = pthsafe_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
