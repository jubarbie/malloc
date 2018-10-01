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

	debug_free(ptr);
	if (ptr != NULL)
	{
		b = (t_block *)ptr;
		b = find_block(ptr);
		if (b != NULL)
			unalloc_block(b);
		else
			debug_print("Trying to free block that was not allocated\n");
	}
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	pthsafe_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}
