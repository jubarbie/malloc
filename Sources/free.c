/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:29:48 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/24 21:39:49 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static t_block	*remove_room(t_block *b, t_block *prev, t_block *next)
{
	if (prev == NULL)
	{
		if (b == g_mem.tiny)
			g_mem.tiny = next;
		if (b == g_mem.small)
			g_mem.small = next;
		if (b == g_mem.medium)
			g_mem.medium = next;
		set_b_prev(next, NULL);
	}
	else
		attach_block(prev, get_b_prev(prev), next);
	munmap((void *)b, block_size(get_b_size(b)));
	return (prev);
}

static t_block	*unalloc_block(t_block *b)
{
	t_block	*next;
	t_block	*prev;

	if (b == NULL)
		return (NULL);
	if (is_b_alloc(b))
		set_b_free(b);
	next = get_b_next(b);
	prev = get_b_prev(b);
	if (is_b_first(b) && (next == NULL || is_b_first(next)))
		return (remove_room(b, prev, next));
	b = defrag_prev(defrag_next(b));
	return (b);
}

void			pthsafe_free(void *ptr)
{
	t_block	*b;

	if (ptr != NULL)
	{
		b = (t_block *)ptr;
		b = find_block(ptr);
		if (b != NULL)
		{
			unalloc_block(b);
		}
	}
	else
		ft_putstr("Trying to free block that was not allocated");
}

void			free(void *ptr)
{
	debug_free(ptr);
	if (ptr != NULL)
	{
		pthread_mutex_lock(&g_mutex);
		pthsafe_free(ptr);
		pthread_mutex_unlock(&g_mutex);
	}
}
