/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_getter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:45:27 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/02 19:34:06 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

char	get_b_first(t_block *ptr)
{
	if (ptr == NULL)
		return (0);
	if (ptr->status & (1 << 2))
		return (1);
	return (0);
}

char	get_b_alloc(t_block *ptr)
{
	if (ptr == NULL)
		return (0);
	if (ptr->status & (1 << 3))
		return (1);
	return (0);
}

size_t	get_b_size(t_block *ptr)
{
	if (ptr == NULL)
		return (0);
	return (ptr->size);
}

t_block	*get_b_next(t_block *ptr)
{
	if (ptr == NULL)
		return (NULL);
	return (ptr->next);
}

t_block	*get_b_prev(t_block *ptr)
{
	if (ptr == NULL)
		return (NULL);
	return (ptr->prev);
}
