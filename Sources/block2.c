/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:34:16 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/01 18:39:30 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*find_block_in_mem(t_block *mem, t_block *block)
{
	t_block *b;

	b = mem;
	while (b != NULL)
	{
		if (b == block)
			return (b);
		b = get_b_next(b);
	}
	return (NULL);
}

t_block	*find_block(void *ptr)
{
	ptr = (t_block *)ptr - 1;
	if (find_block_in_mem(g_mem.tiny, ptr) == (t_block *)ptr)
		return ((t_block *)ptr);
	if (find_block_in_mem(g_mem.small, ptr) == (t_block *)ptr)
		return ((t_block *)ptr);
	if (find_block_in_mem(g_mem.medium, ptr) == (t_block *)ptr)
		return ((t_block *)ptr);
	return (NULL);
}

char	b_cont(t_block *b1, t_block *b2)
{
	if (b1 == NULL || b2 == NULL)
		return (0);
	if (b1 > b2)
		return (0);
	if ((char *)payload(b1) + get_b_size(b1) == (char *)b2)
		return (1);
	return (0);
}