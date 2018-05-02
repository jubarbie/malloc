/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:40:49 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/02 19:33:39 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

t_block	*set_b_first(t_block *ptr)
{
	if (ptr == NULL)
		return (NULL);
	ptr->allocated |= (1 << 1);
	return (ptr);
}

t_block	*set_b(t_block *ptr, size_t size, char alloc)
{
	if (ptr == NULL)
		return (NULL);
	set_b_size(ptr, size);
	set_b_alloc(ptr, alloc);
	return (ptr);
}

t_block	*set_b_next(t_block *ptr, t_block *next)
{
	if (ptr == NULL)
		return (NULL);
	ptr->next = next;
	return (ptr);
}

t_block	*set_b_prev(t_block *ptr, t_block *prev)
{
	if (ptr == NULL)
		return (NULL);
	ptr->prev = prev;
	return (ptr);
}

t_block	*set_b_alloc(t_block *ptr, char alloc)
{
	if (ptr == NULL)
		return (NULL);
	if (alloc == 1)
		ptr->allocated |= (1 << 0);
	else
		ptr->allocated &= ~(1 << 0);
	return (ptr);
}

t_block	*set_b_size(t_block *ptr, size_t size)
{
	if (ptr == NULL)
		return (NULL);
	ptr->size = size;
	return (ptr);
}
