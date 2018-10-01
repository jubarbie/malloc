/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 10:47:30 by jubarbie          #+#    #+#             */
/*   Updated: 2018/10/01 10:47:33 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

t_block	*new_room(size_t size, t_block *prev, t_block *next)
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

t_block	*remove_room(t_block *b, t_block *prev, t_block *next)
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
